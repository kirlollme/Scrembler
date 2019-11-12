#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui_.setupUi(this);
	const auto choose_path_to_file_action = ui_.path_to_file_input->addAction( QIcon( "open.png" ), QLineEdit::TrailingPosition );

	connect(ui_.input_accept_button,		SIGNAL( clicked( ) ),		this,	SLOT(slotInputClicked()));

	connect(ui_.start_button,				SIGNAL( clicked( ) ),		this,	SLOT (slotStart()));
	connect( choose_path_to_file_action,	SIGNAL( triggered( ) ),		this,   SLOT( ChoosePathToFile( ) ) );

	connect(ui_.path_to_file_input,			SIGNAL( editingFinished()) , this , SLOT(slotBlockScrembler()));
	connect(ui_.input,						SIGNAL( editingFinished()) , this , SLOT(slotBlockScrembler()));
	connect(ui_.scrembler_word_input,		SIGNAL(  triggered( )) , this , SLOT(slotBlockScrembler()));

	auto validator = new QIntValidator(0, 10000, this);
	ui_.input->setValidator(validator);
	ui_.period_input->setValidator(new QRegExpValidator(QRegExp("[0-9]{" + QString::number(20)  + "}"),this));							   
	//ui_.period_input->setValidator(new QRegExpValidator(QRegExp("[0-F]{" + QString::number(20)  + "}"),this));
	
}
void MainWindow::slotInputClicked() const
{
	if(ui_.input->text().toULongLong() == 0 || ui_.path_to_file_input->text() == "")
	{
		QMessageBox::information(0, "Ошибка" , "Неправильные входные данные");
		return ;
	}
	settings_.path_to_file =  ui_.path_to_file_input->text();
	settings_.scremblers_count = ui_.input->text().toULongLong();
	settings_.positions_in_code = std::vector<int>(settings_.scremblers_count);
	settings_.word_size = ui_.scrembler_word_input->currentIndex();

	ui_.period_input ->setEnabled(1);
	ui_.period_label ->setEnabled(1);
	disconnect(ui_.table,				 SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(slotTableChanged(QTableWidgetItem *)))  ;
	CreateRows();
	connect(ui_.table,				 SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(slotTableChanged(QTableWidgetItem *)));
}


void MainWindow::slotTableChanged(QTableWidgetItem * itm) const 
{	
	if (!CheckPolinoms())
	{
		QMessageBox::warning(0,"Ошибка","Неправильный ввод полиномов");
		return;
	}
	auto poli_list = itm->text().split(",");
	std::vector <int> polinoms;
	for (auto item : poli_list)
	{
		polinoms.push_back(item.toInt());
	}
	std::sort(polinoms.begin(),polinoms.end(),std::greater<int>());
	
	QString start_pos(polinoms[0],'0');
	for (auto item : polinoms)
	{
		start_pos[polinoms[0] - item] = '1';
	}
	auto col  = itm->column() + 1;
	auto row  = itm->row();
	UpdItem(row,col,polinoms[0],start_pos,settings_.word_size);

}

void MainWindow::slotStart() const
{
	CheckTable();
	time_t start;
	time(&start);
	settings_.scremblers = {};
	settings_.period = ui_.period_input->text().toULongLong();
	for (int i = 0; i < settings_.scremblers_count; i++)
	{
		auto polinoms =  ui_.table->item(i,0)->text();
		auto startpos = GetContent(i,1);
		auto period = GetContent(i,2);
		auto word_size = ui_.scrembler_word_input->currentIndex() + 1;
		Scrembler * scrmblr = new Scrembler(polinoms,startpos,period, word_size);
		settings_.scremblers.push_back(scrmblr);

		auto pos_in_code =  GetContent(i,3).toInt();
		settings_.positions_in_code[pos_in_code - 1] = i;
	}
	code_.Work(settings_.path_to_file, settings_.scremblers ,settings_.positions_in_code,settings_.period);
	code_.processed_bytes_ = 0;
	time_t end;
	time(&end);
	QMessageBox::information(0,"Успешно","Кодировка прошла успешно за " + QString::number(end - start) + "с!");
	Reset();
	return;
}


void MainWindow::CreateRows() const
{
	std::vector <QString> header_list
	{ 
		"Полином",
		"Начальная установка",
		"Период",
		"Номер в кодировании"
	};

	std::vector <QString> size_word 
	{
		"[0-1]{",
		"[0-3]{",
		"[0-7]{",
		"[0-F]{"
	
	};
	ui_.table->setRowCount(0);
	ui_.table->setColumnCount(header_list.size());
	ui_.table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


	for (int i = 0; i < header_list.size(); i++)
	{
		QTableWidgetItem *hnm_1 = new QTableWidgetItem();
		hnm_1->setText(header_list[i]);
		ui_.table->setHorizontalHeaderItem(i, hnm_1);

	}
	
	for (size_t i = 0 ; i < settings_.scremblers_count; i++)
	{
		ui_.table->insertRow(ui_.table->rowCount());

	} 
	// полиномы
	for (size_t i = 0 ; i < settings_.scremblers_count; i++)
	{
		QTableWidgetItem *item = new QTableWidgetItem();
		item->setText("10,8,2");
		ui_.table->setItem(i, 0, item);
	} 
	//начальное состояние
	for (size_t i = 0 ; i < settings_.scremblers_count; i++)
	{
		QLineEdit *edit = new QLineEdit(ui_.table);
		edit->setFrame(false);
		edit->setText("1010000010");
		
		edit->setValidator(new QRegExpValidator(QRegExp( size_word[ ui_.scrembler_word_input->currentIndex( ) ] + QString::number( 10 )  + "}" ) , edit ) );
		ui_.table->setCellWidget(i, 1, edit);
	} 
	// период

	for (size_t i = 0 ; i < settings_.scremblers_count; i++)
	{
		QLineEdit *edit = new QLineEdit(ui_.table);
		edit->setFrame(false);
		edit->setText("1024");
		edit->setValidator(new QIntValidator());	 
		ui_.table->setCellWidget(i, 2, edit);
	}
	// порядок в кодировании
	for (size_t i = 0 ; i < settings_.scremblers_count; i++)
	{
		QLineEdit *edit = new QLineEdit(ui_.table);
		edit->setFrame(false);
		edit->setValidator(new QIntValidator(1, settings_.scremblers_count, edit));	 
		edit->setText(QString::number(i+1));
		ui_.table->setCellWidget(i, 3, edit);
	} 
	ui_.table				-> setEnabled(1);
}

void MainWindow::slotBlockScrembler() const
{
	ui_.table ->setEnabled(0);
	ui_.period_input->setEnabled(0);
	ui_.period_label->setEnabled(0);
}



bool MainWindow::CheckPolinoms() const
{
	for (int i = 0 ; i < settings_.scremblers_count ; i++)
	{
		auto str = ui_.table->item(i,0)->text();
		for(int j = 0 ; j < str.size(); j++)
		{
			if((str[j].toLatin1() - '0' >= 0 && str[j].toLatin1() - '0' <= 9) || str[j] == " " || str[j] == ",")
				continue;
			else
				return false;
		}
	}
	return true;
}

void MainWindow::UpdItem(int row, int col, int value, QString str,int bit_size) const
{
	std::vector <QString> size_word 
	{
		"[0-1]{",
		"[0-3]{",
		"[0-7]{",
		"[0-F]{"

	};
	QLineEdit *edit = new QLineEdit(this->ui_.table);
	edit->setText(str);
	edit->setFrame(false);
	edit->setValidator(new QRegExpValidator(QRegExp( size_word[bit_size] + QString::number(value)  + "}"), edit));
	this->ui_.table->setCellWidget(row, col, edit);
}

bool MainWindow::CheckTable() const
{
	if (!CheckPolinoms())
	{
		QMessageBox::warning(0, "Ошибка", "Неправильный ввод полиномов");
		return false;
	}
	if (!CheckPositions())
	{	
		QMessageBox::warning(0, "Ошибка", "Неправильный ввод позиций");
		return false;
	}
	if(ui_.period_input->text().toULongLong() == 0)
	{
		QMessageBox::warning(0, "Ошибка", "Неправильный период");
		return false;
	}
	return true;
}

bool MainWindow::CheckPositions() const
{
	std::vector <bool> check(settings_.scremblers_count);
	for (int i = 0 ; i < settings_.scremblers_count ; i++)
	{
		auto content = GetContent(i,3);
		auto num = content.toInt();
		if(check[num - 1])
			return false;
		else 
			check[num - 1] = true;
	}
	return true;
}

void MainWindow::Reset() const
{
	 ui_.table->setRowCount(0);
	 ui_.table->setColumnCount(0);
	 ui_.table->setEnabled(0);
	 ui_.period_input->setEnabled(0);
	 ui_.period_label->setEnabled(0);

}

QString MainWindow::GetContent(int row,int col)	const
{
	QWidget* cell = ui_.table->cellWidget(row,col);
	auto line = dynamic_cast<QLineEdit*>(cell);
	return line->text();
}

void MainWindow::ChoosePathToFile( ) 
{
	auto file_name = QFileDialog::getOpenFileName( this, tr( "Open file" ), settings_.path_to_file );

	if( !file_name.isEmpty( ) )
	{
			ui_.path_to_file_input->setText( file_name );
	}
}
