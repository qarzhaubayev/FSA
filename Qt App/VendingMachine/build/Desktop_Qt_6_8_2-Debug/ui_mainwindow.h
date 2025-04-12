/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *labelBalance;
    QListWidget *listProducts;
    QComboBox *comboCoin;
    QPushButton *btnInsert;
    QPushButton *btnBuy;
    QPushButton *btnAdmin;
    QPlainTextEdit *txtLog;
    QMenuBar *menubar;
    QMenu *menuVending_Machine;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1289, 785);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        labelBalance = new QLabel(centralwidget);
        labelBalance->setObjectName("labelBalance");
        labelBalance->setGeometry(QRect(100, 80, 141, 17));
        listProducts = new QListWidget(centralwidget);
        listProducts->setObjectName("listProducts");
        listProducts->setGeometry(QRect(310, 30, 256, 192));
        comboCoin = new QComboBox(centralwidget);
        comboCoin->setObjectName("comboCoin");
        comboCoin->setGeometry(QRect(630, 90, 86, 25));
        btnInsert = new QPushButton(centralwidget);
        btnInsert->setObjectName("btnInsert");
        btnInsert->setGeometry(QRect(350, 380, 89, 25));
        btnBuy = new QPushButton(centralwidget);
        btnBuy->setObjectName("btnBuy");
        btnBuy->setGeometry(QRect(90, 380, 191, 25));
        btnAdmin = new QPushButton(centralwidget);
        btnAdmin->setObjectName("btnAdmin");
        btnAdmin->setGeometry(QRect(520, 380, 251, 25));
        txtLog = new QPlainTextEdit(centralwidget);
        txtLog->setObjectName("txtLog");
        txtLog->setGeometry(QRect(280, 530, 361, 71));
        txtLog->setReadOnly(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1289, 22));
        menuVending_Machine = new QMenu(menubar);
        menuVending_Machine->setObjectName("menuVending_Machine");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuVending_Machine->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        labelBalance->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        btnInsert->setText(QCoreApplication::translate("MainWindow", "Insert Coin", nullptr));
        btnBuy->setText(QCoreApplication::translate("MainWindow", "Buy product", nullptr));
        btnAdmin->setText(QCoreApplication::translate("MainWindow", "Insert Product (Admin only)", nullptr));
        txtLog->setPlaceholderText(QCoreApplication::translate("MainWindow", "Messages will appear here...", nullptr));
        menuVending_Machine->setTitle(QCoreApplication::translate("MainWindow", "Vending Machine", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
