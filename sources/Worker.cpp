#include "Worker.h"



Worker::Worker(Settings& setup)
{
	for (int i = 0 ; i  < setup.scremblers.size() ; i++)
	{
		auto set_scr = setup.scremblers[i];
		auto src = new Scrembler(*set_scr) ;
		scremblers_.push_back( src );
	}
	processed_bytes_ = 0;
	positions_in_code_ = setup.positions_in_code;
	period = setup.period;
	path_to_file_ = setup.path_to_file; 
	QFile file( path_to_file_ );
	GetFileConfig(file);
	StartEncode();
}

void Worker::StartEncode()
{
	QFile file( path_to_file_ );
	if ( !file.open( QFile::ReadOnly ) )
	{
		QMessageBox::warning(0,"Ошибка во время выполнения","Не удалось открыть файл");
		return;
	}
	file.open( QFile::ReadOnly );
	EncodeFile(file);
	CreateConfig();
	file.close();

}

void Worker::CreateConfig()
{
	auto file_name_out = base_name_;

	auto path = dir_path_ + base_name_+"_p"+QString::number(period)  + "_config" + ".txt";
	QFile file( path );
	file.open(QIODevice::WriteOnly);
	QString info = "";

	info += "total period : " +QString::number(period) + '\n';
	info += "number of scramblers : " +QString::number(scremblers_.size()) + '\n';


	for (int i = 0 ; i < scremblers_.size(); i++)
	{
		info += "Scrembler "+ QString::number(i + 1) + ": \n";
		info += "\t Word size (bit) : " +  QString::number(scremblers_[i]->word_len_) + "\n"  ;
		info += "\t Polinoms : " + scremblers_[i]->polinoms_str_ + "\n"  ;
		info += "\t Start pos : " + scremblers_[i]->start_pos_str_ + "\n"  ;
		info += "\t Period : " + scremblers_[i]->period_str_ + "\n"  ;
		info += "\t Encoding number : " + QString::number(positions_in_code_[i]+ 1) + "\n"  ;

	}

	file.write(info.toUtf8());
	file.close();
}

void Worker::Save(QByteArray & buffer)
{
	auto file_name_out = base_name_;

	auto path = dir_path_ + base_name_ + "_p"+QString::number(period) +"_Encode." +suffix_;

	QFile out_file( path );
	if (new_file_)
		out_file.open(QIODevice::WriteOnly);
	else
		out_file.open(QIODevice::Append);
	out_file.write(buffer);
	out_file.close();

}

void Worker::GetFileConfig(QFile& file)
{
	file_name_  = file.fileName();
	auto file_info = QFileInfo(file);
	base_name_ = file_info.baseName();
	dir_path_ =	 path_to_file_.mid(0, path_to_file_.size() - file_info.fileName().size());
	suffix_ = file_info.completeSuffix();
}

void Worker::EncodeFile(QFile& file)
{
	QByteArray buffer;
	size_t a = file.size();
	while (processed_bytes_ < file.size())
	{
		processed_bytes_ +=buffer_size_;
		buffer = file.read( buffer_size_ );
		encoder_.Encode(buffer, scremblers_, positions_in_code_,period);
		Save(buffer);
		new_file_ = false;
	}
	new_file_ = true;
}
