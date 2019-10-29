#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <ctime>
#include <QMessageBox>
#include <QValidator>

#include "Scrembler.h"
#include "Encoder.h"
#include "reader.h"

#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileDialog>
#include <QAction>
#include <QFile>
#include <QDir>
#include <QFileInfo>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

	mutable size_t scremblers_count_	{ 0 };
	
	mutable QString path_to_file_		{	};

	mutable std::vector <Scrembler*> scremblers_{  };

	mutable std::vector <int> positions_in_code_ {};
	 
	mutable size_t period_;
	 

	void CreateRows() const;

	QString GetContent(int row,int col) const;

	bool CheckPolinoms() const;
	void UpdItem (int row, int col, int value,QString str) const;

	bool CheckTable() const;
	bool CheckPositions() const;
	void Reset() const;
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

public slots:
	void slotBlockScrembler() const ;
	void ChoosePathToFile() ;
	void slotInputClicked() const;
	void slotTableChanged(QTableWidgetItem * itm) const;
	void slotStart() const;

private:
    Ui::MainWindow ui_;
};

#endif // MAINWINDOW_H
