#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <ctime>
#include <QMessageBox>
#include <QValidator>

#include "Scrembler.h"
#include "Worker.h"
#include "ui_mainwindow.h"
#include "defs.h"

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

	mutable Settings settings_;

	mutable Worker code_;

	void CreateRows() const;

	QString GetContent(int row,int col) const;

	bool CheckPolinoms() const;
	void UpdItem (int row, int col, int value,QString str,int bit_size) const;

	bool CheckTable() const;
	bool CheckPositions() const;
	void Reset() const;

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
