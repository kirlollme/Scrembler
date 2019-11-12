#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QValidator>
#include <ctime>
#include <vector>

#include "Scrembler.h"
#include "Worker.h"
#include "defs.h"
#include "ui_mainwindow.h"
#include <memory>

#include <QAction>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QStandardItem>
#include <QStandardItemModel>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

  mutable Settings settings_;

  mutable Worker* encoder_;

  void CreateRows() const;

  QString GetContentLineEdit(int row, int col) const;

  bool CheckPolinoms() const;
  void UpdItem(int row, int col, int value, QString str, int bit_size) const;

  bool CheckTable() const;
  bool CheckPositions() const;
  void Reset() const;
  void GetScremblerSettings() const;

public slots:
  void slotBlockScrembler() const;
  void ChoosePathToFile();
  void slotInputClicked() const;
  void slotTableChanged(QTableWidgetItem *itm) const;
  void slotStart() const;
  void slotChangeType(int) const;

private:
  Ui::MainWindow ui_;
};

#endif // MAINWINDOW_H
