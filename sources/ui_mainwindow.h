/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLineEdit *path_to_file_input;
    QLineEdit *period_input;
    QPushButton *input_accept_button;
    QSpacerItem *horizontalSpacer;
    QLabel *path_to_file_label;
    QPushButton *start_button;
    QComboBox *scrembler_word_input;
    QTableWidget *table;
    QLabel *period_label;
    QLineEdit *input;
    QSpacerItem *horizontalSpacer_2;
    QLabel *input_label;
    QLabel *scrembler_word_label;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(729, 635);
        MainWindow->setMinimumSize(QSize(600, 500));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(10);
        sizePolicy.setVerticalStretch(10);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(0, 0));
        centralWidget->setSizeIncrement(QSize(1, 1));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        path_to_file_input = new QLineEdit(centralWidget);
        path_to_file_input->setObjectName(QString::fromUtf8("path_to_file_input"));

        gridLayout->addWidget(path_to_file_input, 1, 1, 1, 1);

        period_input = new QLineEdit(centralWidget);
        period_input->setObjectName(QString::fromUtf8("period_input"));
        period_input->setEnabled(false);

        gridLayout->addWidget(period_input, 5, 5, 1, 1);

        input_accept_button = new QPushButton(centralWidget);
        input_accept_button->setObjectName(QString::fromUtf8("input_accept_button"));

        gridLayout->addWidget(input_accept_button, 3, 5, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 2, 1, 1);

        path_to_file_label = new QLabel(centralWidget);
        path_to_file_label->setObjectName(QString::fromUtf8("path_to_file_label"));

        gridLayout->addWidget(path_to_file_label, 0, 1, 1, 1);

        start_button = new QPushButton(centralWidget);
        start_button->setObjectName(QString::fromUtf8("start_button"));
        start_button->setEnabled(true);

        gridLayout->addWidget(start_button, 9, 5, 1, 1);

        scrembler_word_input = new QComboBox(centralWidget);
        scrembler_word_input->addItem(QString());
        scrembler_word_input->addItem(QString());
        scrembler_word_input->addItem(QString());
        scrembler_word_input->addItem(QString());
        scrembler_word_input->setObjectName(QString::fromUtf8("scrembler_word_input"));

        gridLayout->addWidget(scrembler_word_input, 5, 1, 1, 1);

        table = new QTableWidget(centralWidget);
        table->setObjectName(QString::fromUtf8("table"));
        table->setEnabled(false);
        table->setMinimumSize(QSize(0, 400));
        table->setMaximumSize(QSize(16777215, 16777215));

        gridLayout->addWidget(table, 8, 1, 1, 5);

        period_label = new QLabel(centralWidget);
        period_label->setObjectName(QString::fromUtf8("period_label"));
        period_label->setEnabled(false);

        gridLayout->addWidget(period_label, 5, 4, 1, 1);

        input = new QLineEdit(centralWidget);
        input->setObjectName(QString::fromUtf8("input"));

        gridLayout->addWidget(input, 3, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 3, 1, 1);

        input_label = new QLabel(centralWidget);
        input_label->setObjectName(QString::fromUtf8("input_label"));

        gridLayout->addWidget(input_label, 2, 1, 1, 1);

        scrembler_word_label = new QLabel(centralWidget);
        scrembler_word_label->setObjectName(QString::fromUtf8("scrembler_word_label"));

        gridLayout->addWidget(scrembler_word_label, 4, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Add Scrembled", nullptr));
        period_input->setText(QCoreApplication::translate("MainWindow", "1024", nullptr));
        input_accept_button->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\275\321\217\321\202\321\214", nullptr));
        path_to_file_label->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\264\320\276 \321\204\320\260\320\271\320\273\320\260", nullptr));
        start_button->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\272\320\276\320\264\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        scrembler_word_input->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        scrembler_word_input->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        scrembler_word_input->setItemText(2, QCoreApplication::translate("MainWindow", "3", nullptr));
        scrembler_word_input->setItemText(3, QCoreApplication::translate("MainWindow", "4", nullptr));

        period_label->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\211\320\270\320\271 \320\277\320\265\321\200\320\270\320\276\320\264", nullptr));
        input_label->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\201\321\200\320\265\320\274\320\261\320\273\320\265\321\200\320\276\320\262", nullptr));
        scrembler_word_label->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\261\320\270\321\202 \320\262 \321\217\321\207\320\265\320\271\320\272\320\265 \321\201\320\272\321\200\320\265\320\274\320\261\320\273\320\265\321\200\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
