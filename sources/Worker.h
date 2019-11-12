#pragma once
#include <QString>
#include <vector>
#include "Scrembler.h"
#include <QFile>  
#include <QFileInfo>
#include <QMessageBox>
#include "Encoder.h"
struct Worker
{
	void Work(QString path_to_file, std::vector<Scrembler*>& scremblers, std::vector<int> const & positions_in_code,size_t period );
	void Config(std::vector<Scrembler*>& scremblers, std::vector<int> const & positions_in_code, size_t period);
	void Save(QByteArray& buffer,size_t period);
	QString file_name; 
	QString base_name;
	QString dir_path;
	QString suffix;
	bool new_file = true;
	size_t processed_bytes_ {0};
	size_t const buffer_size_	{128 * 1024 * 1024};
};