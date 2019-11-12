#include "Worker.h"

void Worker::Work(QString path_to_file, std::vector<Scrembler*>& scremblers, std::vector<int> const & positions_in_code,size_t period)
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

void Worker::Config(std::vector<Scrembler*>& scremblers, std::vector<int> const & positions_in_code, size_t period)
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
		info += "\t Word size (bit) : " +  QString::number(scremblers[i]->word_len) + "\n"  ;
		info += "\t Polinoms : " + scremblers[i]->polinoms_str + "\n"  ;
		info += "\t Start pos : " + scremblers[i]->start_pos_str + "\n"  ;
		info += "\t Period : " + scremblers[i]->period_str + "\n"  ;
		info += "\t Encoding number : " + QString::number(positions_in_code[i]+ 1) + "\n"  ;

	}

	file.write(info.toUtf8());
	file.close();
}

void Worker::Save(QByteArray & buffer,size_t period)
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
