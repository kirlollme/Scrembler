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

	auto validator = new QIntValidator(0, 10000, this);
	ui_.input->setValidator(validator);
	ui_.period_input->setValidator(new QRegExpValidator(QRegExp("[0-9]{" + QString::number(20)  + "}"),this));							   

	
}
void MainWindow::slotInputClicked() const
{
	if(ui_.input->text().toULongLong() == 0 || ui_.path_to_file_input->text() == "")
	{
		QMessageBox::information(0, "Ошибка" , "Неправильные входные данные");
		return ;
	}
	path_to_file_ =  ui_.path_to_file_input->text();
	scremblers_count_ = ui_.input->text().toULongLong();
	positions_in_code_ = std::vector<int>(scremblers_count_);

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
	auto col  = itm->column() + 3;
	auto row  = itm->row();
	UpdItem(row,col,polinoms[0],start_pos);

}

void MainWindow::slotStart() const
{
	CheckTable();
	time_t start;
	time(&start);
	scremblers_ = {};
	period_ = ui_.period_input->text().toULongLong();
	for (int i = 0; i < scremblers_count_; i++)
	{
		auto polinoms =  ui_.table->item(i,0)->text();
		auto startpos = GetContent(i,1);
		auto period = GetContent(i,2);
		auto word_size = ui_.scrembler_word_input->currentIndex()	;
		Scrembler * scrmblr = new Scrembler(polinoms,startpos,period, word_size);
		scremblers_.push_back(scrmblr);

		auto pos_in_code =  GetContent(i,3).toInt();
		positions_in_code_[pos_in_code - 1] = i;
	}
	Worker Todo;
	Todo.Work(path_to_file_,scremblers_,positions_in_code_,period_);
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
		"Тип скремблера",
		"Номер в кодировании",
		"Начальная установка",
		"Период"
		//"Номер в кодировании"
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
	ui_.table->setEnabled(1);

	for (int i = 0; i < header_list.size(); i++)
	{
		QTableWidgetItem *hnm_1 = new QTableWidgetItem();
		hnm_1->setText(header_list[i]);
		ui_.table->setHorizontalHeaderItem(i, hnm_1);

	}
	
	for (size_t i = 0 ; i < scremblers_count_; i++)
	{
		ui_.table->insertRow(ui_.table->rowCount());

	} 
	// полиномы
	for (size_t i = 0 ; i < scremblers_count_; i++)
	{
		QTableWidgetItem *item = new QTableWidgetItem();
		item->setText("10,8,2");
		ui_.table->setItem(i, 0, item);
	} 
	// вид скремблера
	for (size_t i = 0; i < scremblers_count_; i++)
	{
		QComboBox *item = new QComboBox();
		item->addItem("Мультипликативный",0);
		item->addItem("Аддитивный",1);
		item->setFrame(false);
		ui_.table->setCellWidget(i, 1, item);
	}
	// порядок в кодировании
	for (size_t i = 0; i < scremblers_count_; i++)
	{
		QLineEdit *edit = new QLineEdit(ui_.table);
		edit->setFrame(false);
		edit->setValidator(new QIntValidator(1, scremblers_count_, edit));
		edit->setText(QString::number(i + 1));
		ui_.table->setCellWidget(i, 2, edit);
	}

	//начальное состояние
	for (size_t i = 0 ; i < scremblers_count_; i++)
	{
		QLineEdit *edit = new QLineEdit(ui_.table);
		edit->setFrame(false);
		edit->setText("1010000010");
		
		edit->setValidator(new QRegExpValidator(QRegExp( size_word[ ui_.scrembler_word_input->currentIndex( ) ] + QString::number( 10 )  + "}" ) , edit ) );
		ui_.table->setCellWidget(i, 3, edit);
		//ui_.table->item.setEnabled(0);
	} 
	// период

	for (size_t i = 0 ; i < scremblers_count_; i++)
	{
		QLineEdit *edit = new QLineEdit(ui_.table);
		edit->setFrame(false);
		edit->setText("1024");
		edit->setValidator(new QIntValidator());	
		//edit->setEnabled(0);
		ui_.table->setCellWidget(i, 4, edit);

	}
	//connect(ui_.table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(slotChangeType(int,int)));
	connect(ui_.table, SIGNAL(cellClicked(int, int)),
		this, SLOT(slotChangeType(int, int)));
}
void MainWindow::slotChangeType(int col,int row) const
{
	QMessageBox::information(0, " ",
		"Cell at row "+QString::number(row)+
		" column "+QString::number(col)+
		" was double clicked.");

}

void MainWindow::slotBlockScrembler() const
{
	ui_.table ->setEnabled(0);
	ui_.period_input->setEnabled(0);
	ui_.period_label->setEnabled(0);
}



bool MainWindow::CheckPolinoms() const
{
	for (int i = 0 ; i < scremblers_count_ ; i++)
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

void MainWindow::UpdItem(int row, int col, int value, QString str) const
{
	QLineEdit *edit = new QLineEdit(this->ui_.table);
	edit->setText(str);
	edit->setFrame(false);
	edit->setValidator(new QRegExpValidator(QRegExp("[0-1]{" + QString::number(value)  + "}"), edit));
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
	std::vector <bool> check(scremblers_count_);
	for (int i = 0 ; i < scremblers_count_ ; i++)
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
	auto file_name = QFileDialog::getOpenFileName( this, tr( "Open file" ), path_to_file_ );

	if( !file_name.isEmpty( ) )
	{
			ui_.path_to_file_input->setText( file_name );
	}
}


void MainWindow::Worker::Work(QString path_to_file, std::vector<Scrembler*>& scremblers, std::vector<int> const & positions_in_code,size_t period)
{
	QFile file( path_to_file );

	file_name  = file.fileName();
	auto file_info = QFileInfo(file);
	base_name = file_info.baseName();
	dir_path =	 path_to_file.mid(0, path_to_file.size() - file_info.fileName().size());
	suffix = file_info.completeSuffix();
	if ( !file.open( QFile::ReadOnly ) )
	{
		QMessageBox::warning(0,"Ошибка во время выполнения","Не удалось открыть файл");
		return;
	}
	file.open( QFile::ReadOnly );
	QByteArray buffer;
	size_t a = file.size();
	while (processed_bytes_ < file.size())
	{
		processed_bytes_ +=buffer_size_;
		buffer = file.read( buffer_size_ );
		Encode(buffer, scremblers, positions_in_code,period);
		Save(buffer,period);
		new_file = false;
	}
	new_file = true;
	Config(scremblers,positions_in_code,period);
	file.close();
	// TODO: вставьте здесь оператор return
}

void MainWindow::Worker::Config(std::vector<Scrembler*>& scremblers, std::vector<int> const & positions_in_code, size_t period)
{
	auto file_name_out = base_name;

	auto path = dir_path + base_name+"_p"+QString::number(period)  + "_config" + ".txt";
	QFile file( path );
	file.open(QIODevice::WriteOnly);
	QString info = "";

	info += "total period : " +QString::number(period) + '\n';
	info += "number of scramblers : " +QString::number(scremblers.size()) + '\n';


	for (int i = 0 ; i < scremblers.size(); i++)
	{
		info += "Scrembler "+ QString::number(i + 1) + ": \n";
		info += "\t Polinoms : " + scremblers[i]->polinoms_str + "\n"  ;
		info += "\t Start pos : " + scremblers[i]->start_pos_str + "\n"  ;
		info += "\t Period : " + scremblers[i]->period_str + "\n"  ;
		info += "\t Encoding number : " + QString::number(positions_in_code[i]+ 1) + "\n"  ;
	
	}

	file.write(info.toUtf8());
	file.close();
}

void MainWindow::Worker::Save(QByteArray & buffer,size_t period)
{
	auto file_name_out = base_name;

	auto path = dir_path + base_name + "_p"+QString::number(period) +"_Encode." +suffix;
	
	QFile file( path );
	if (new_file)
		file.open(QIODevice::WriteOnly);
	else
		file.open(QIODevice::Append);
	file.write(buffer);
	file.close();

}
