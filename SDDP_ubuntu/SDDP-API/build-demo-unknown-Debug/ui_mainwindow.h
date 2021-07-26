/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action2;
    QAction *action1_1;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox;
    QPushButton *self_button;
    QPushButton *manual_button;
    QLabel *label_mode;
    QGroupBox *groupBox_2;
    QPushButton *steerEnableButton;
    QPushButton *steerDisableButton;
    QPushButton *steerSetButton;
    QPushButton *steerAddButton;
    QPushButton *steerSubButton;
    QLineEdit *objSteer;
    QLabel *label_4;
    QLabel *label_nowSteer;
    QLabel *label_steerStatus;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QLineEdit *lineEdit_2;
    QLabel *label_6;
    QLabel *label_nowAcc;
    QLabel *label_accStatus;
    QGroupBox *groupBox_4;
    QPushButton *InitSButton;
    QPushButton *unintServiceButton;
    QGroupBox *groupBox_5;
    QPushButton *setNGearButton;
    QPushButton *setDGearButton;
    QLabel *label_nowGear;
    QPushButton *setRGearButton;
    QPushButton *setPGearButton;
    QGroupBox *groupBox_6;
    QPushButton *pushButton_15;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QGroupBox *groupBox_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_nowSpeed;
    QLabel *label_nowBattery;
    QLabel *label_nowEngine;
    QLabel *label_nowBOpening;
    QLabel *label_nowTOpening;
    QGroupBox *groupBox_8;
    QLabel *label_connectStatus;
    QGroupBox *groupBox_9;
    QPushButton *pushButton_18;
    QLabel *label;
    QLabel *label_nowTime;
    QGroupBox *groupBox_10;
    QWidget *tab_2;
    QWidget *tab_3;
    QWidget *tab_4;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuA;
    QMenu *menuB;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(914, 407);
        action2 = new QAction(MainWindow);
        action2->setObjectName(QString::fromUtf8("action2"));
        action1_1 = new QAction(MainWindow);
        action1_1->setObjectName(QString::fromUtf8("action1_1"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 911, 381));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 121, 101));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(135, 213, 255);\n"
"\n"
""));
        self_button = new QPushButton(groupBox);
        self_button->setObjectName(QString::fromUtf8("self_button"));
        self_button->setGeometry(QRect(10, 20, 101, 27));
        manual_button = new QPushButton(groupBox);
        manual_button->setObjectName(QString::fromUtf8("manual_button"));
        manual_button->setGeometry(QRect(10, 50, 101, 27));
        label_mode = new QLabel(groupBox);
        label_mode->setObjectName(QString::fromUtf8("label_mode"));
        label_mode->setGeometry(QRect(30, 80, 71, 20));
        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(140, 10, 191, 101));
        groupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        steerEnableButton = new QPushButton(groupBox_2);
        steerEnableButton->setObjectName(QString::fromUtf8("steerEnableButton"));
        steerEnableButton->setGeometry(QRect(0, 20, 91, 27));
        steerDisableButton = new QPushButton(groupBox_2);
        steerDisableButton->setObjectName(QString::fromUtf8("steerDisableButton"));
        steerDisableButton->setGeometry(QRect(100, 20, 91, 27));
        steerSetButton = new QPushButton(groupBox_2);
        steerSetButton->setObjectName(QString::fromUtf8("steerSetButton"));
        steerSetButton->setGeometry(QRect(80, 50, 41, 27));
        steerAddButton = new QPushButton(groupBox_2);
        steerAddButton->setObjectName(QString::fromUtf8("steerAddButton"));
        steerAddButton->setGeometry(QRect(130, 50, 31, 27));
        steerSubButton = new QPushButton(groupBox_2);
        steerSubButton->setObjectName(QString::fromUtf8("steerSubButton"));
        steerSubButton->setGeometry(QRect(160, 50, 31, 27));
        objSteer = new QLineEdit(groupBox_2);
        objSteer->setObjectName(QString::fromUtf8("objSteer"));
        objSteer->setGeometry(QRect(0, 50, 71, 27));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 80, 41, 17));
        label_nowSteer = new QLabel(groupBox_2);
        label_nowSteer->setObjectName(QString::fromUtf8("label_nowSteer"));
        label_nowSteer->setGeometry(QRect(60, 80, 31, 17));
        label_steerStatus = new QLabel(groupBox_2);
        label_steerStatus->setObjectName(QString::fromUtf8("label_steerStatus"));
        label_steerStatus->setGeometry(QRect(120, 80, 67, 17));
        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(340, 10, 191, 101));
        groupBox_3->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 255, 255);"));
        pushButton_6 = new QPushButton(groupBox_3);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(0, 20, 91, 27));
        pushButton_7 = new QPushButton(groupBox_3);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(100, 20, 91, 27));
        pushButton_8 = new QPushButton(groupBox_3);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(80, 50, 41, 27));
        pushButton_9 = new QPushButton(groupBox_3);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(130, 50, 31, 27));
        pushButton_10 = new QPushButton(groupBox_3);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(160, 50, 31, 27));
        lineEdit_2 = new QLineEdit(groupBox_3);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(0, 50, 71, 27));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 80, 31, 17));
        label_nowAcc = new QLabel(groupBox_3);
        label_nowAcc->setObjectName(QString::fromUtf8("label_nowAcc"));
        label_nowAcc->setGeometry(QRect(70, 80, 67, 17));
        label_accStatus = new QLabel(groupBox_3);
        label_accStatus->setObjectName(QString::fromUtf8("label_accStatus"));
        label_accStatus->setGeometry(QRect(120, 80, 61, 16));
        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 120, 121, 101));
        groupBox_4->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 255);"));
        InitSButton = new QPushButton(groupBox_4);
        InitSButton->setObjectName(QString::fromUtf8("InitSButton"));
        InitSButton->setGeometry(QRect(10, 20, 99, 27));
        unintServiceButton = new QPushButton(groupBox_4);
        unintServiceButton->setObjectName(QString::fromUtf8("unintServiceButton"));
        unintServiceButton->setGeometry(QRect(10, 60, 99, 27));
        groupBox_5 = new QGroupBox(tab);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(140, 120, 141, 101));
        groupBox_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        setNGearButton = new QPushButton(groupBox_5);
        setNGearButton->setObjectName(QString::fromUtf8("setNGearButton"));
        setNGearButton->setGeometry(QRect(10, 20, 61, 27));
        setDGearButton = new QPushButton(groupBox_5);
        setDGearButton->setObjectName(QString::fromUtf8("setDGearButton"));
        setDGearButton->setGeometry(QRect(70, 20, 61, 27));
        label_nowGear = new QLabel(groupBox_5);
        label_nowGear->setObjectName(QString::fromUtf8("label_nowGear"));
        label_nowGear->setGeometry(QRect(60, 80, 41, 17));
        setRGearButton = new QPushButton(groupBox_5);
        setRGearButton->setObjectName(QString::fromUtf8("setRGearButton"));
        setRGearButton->setGeometry(QRect(10, 50, 61, 27));
        setPGearButton = new QPushButton(groupBox_5);
        setPGearButton->setObjectName(QString::fromUtf8("setPGearButton"));
        setPGearButton->setGeometry(QRect(70, 50, 61, 27));
        groupBox_6 = new QGroupBox(tab);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(290, 120, 241, 101));
        groupBox_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_15 = new QPushButton(groupBox_6);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));
        pushButton_15->setGeometry(QRect(20, 20, 99, 27));
        pushButton_16 = new QPushButton(groupBox_6);
        pushButton_16->setObjectName(QString::fromUtf8("pushButton_16"));
        pushButton_16->setGeometry(QRect(130, 20, 99, 27));
        pushButton_17 = new QPushButton(groupBox_6);
        pushButton_17->setObjectName(QString::fromUtf8("pushButton_17"));
        pushButton_17->setGeometry(QRect(50, 60, 151, 27));
        groupBox_7 = new QGroupBox(tab);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(540, 9, 181, 301));
        groupBox_7->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 57 italic 11pt \"Ubuntu\";"));
        label_8 = new QLabel(groupBox_7);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 30, 91, 17));
        label_9 = new QLabel(groupBox_7);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 60, 81, 17));
        label_10 = new QLabel(groupBox_7);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 90, 67, 17));
        label_11 = new QLabel(groupBox_7);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 120, 111, 17));
        label_12 = new QLabel(groupBox_7);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 150, 131, 17));
        label_nowSpeed = new QLabel(groupBox_7);
        label_nowSpeed->setObjectName(QString::fromUtf8("label_nowSpeed"));
        label_nowSpeed->setGeometry(QRect(130, 30, 67, 17));
        label_nowBattery = new QLabel(groupBox_7);
        label_nowBattery->setObjectName(QString::fromUtf8("label_nowBattery"));
        label_nowBattery->setGeometry(QRect(130, 60, 67, 17));
        label_nowEngine = new QLabel(groupBox_7);
        label_nowEngine->setObjectName(QString::fromUtf8("label_nowEngine"));
        label_nowEngine->setGeometry(QRect(130, 90, 67, 17));
        label_nowBOpening = new QLabel(groupBox_7);
        label_nowBOpening->setObjectName(QString::fromUtf8("label_nowBOpening"));
        label_nowBOpening->setGeometry(QRect(130, 120, 67, 17));
        label_nowTOpening = new QLabel(groupBox_7);
        label_nowTOpening->setObjectName(QString::fromUtf8("label_nowTOpening"));
        label_nowTOpening->setGeometry(QRect(130, 150, 67, 17));
        groupBox_8 = new QGroupBox(tab);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 230, 120, 80));
        groupBox_8->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_connectStatus = new QLabel(groupBox_8);
        label_connectStatus->setObjectName(QString::fromUtf8("label_connectStatus"));
        label_connectStatus->setGeometry(QRect(20, 40, 61, 20));
        label_connectStatus->setStyleSheet(QString::fromUtf8("font: 57 italic 16pt \"Ubuntu\";"));
        groupBox_9 = new QGroupBox(tab);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(140, 230, 391, 80));
        groupBox_9->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_18 = new QPushButton(tab);
        pushButton_18->setObjectName(QString::fromUtf8("pushButton_18"));
        pushButton_18->setGeometry(QRect(10, 310, 521, 21));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 330, 441, 21));
        label_nowTime = new QLabel(tab);
        label_nowTime->setObjectName(QString::fromUtf8("label_nowTime"));
        label_nowTime->setGeometry(QRect(530, 319, 341, 31));
        label_nowTime->setStyleSheet(QString::fromUtf8("font: 75 oblique 12pt \"Waree\";\n"
"gridline-color: rgb(255, 85, 255);"));
        groupBox_10 = new QGroupBox(tab);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setGeometry(QRect(730, 9, 181, 301));
        groupBox_10->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidget->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 914, 25));
        menuA = new QMenu(menuBar);
        menuA->setObjectName(QString::fromUtf8("menuA"));
        menuB = new QMenu(menuBar);
        menuB->setObjectName(QString::fromUtf8("menuB"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuA->menuAction());
        menuBar->addAction(menuB->menuAction());

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action2->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        action1_1->setText(QApplication::translate("MainWindow", "1.1", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "2->Mode", 0, QApplication::UnicodeUTF8));
        self_button->setText(QApplication::translate("MainWindow", "Self-Driving", 0, QApplication::UnicodeUTF8));
        manual_button->setText(QApplication::translate("MainWindow", "Manual", 0, QApplication::UnicodeUTF8));
        label_mode->setText(QApplication::translate("MainWindow", "Unknow", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "3->Steer", 0, QApplication::UnicodeUTF8));
        steerEnableButton->setText(QApplication::translate("MainWindow", "Enable", 0, QApplication::UnicodeUTF8));
        steerDisableButton->setText(QApplication::translate("MainWindow", "Disable", 0, QApplication::UnicodeUTF8));
        steerSetButton->setText(QApplication::translate("MainWindow", "Set", 0, QApplication::UnicodeUTF8));
        steerAddButton->setText(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
        steerSubButton->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "steer:", 0, QApplication::UnicodeUTF8));
        label_nowSteer->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_steerStatus->setText(QApplication::translate("MainWindow", "Enable", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "5->Acceleration", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("MainWindow", "Enable", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("MainWindow", "Disable", 0, QApplication::UnicodeUTF8));
        pushButton_8->setText(QApplication::translate("MainWindow", "Set", 0, QApplication::UnicodeUTF8));
        pushButton_9->setText(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
        pushButton_10->setText(QApplication::translate("MainWindow", "-", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "acc:", 0, QApplication::UnicodeUTF8));
        label_nowAcc->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_accStatus->setText(QApplication::translate("MainWindow", "Enable", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "1->Service", 0, QApplication::UnicodeUTF8));
        InitSButton->setText(QApplication::translate("MainWindow", "InitService", 0, QApplication::UnicodeUTF8));
        unintServiceButton->setText(QApplication::translate("MainWindow", "UnintService", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "4->Gear", 0, QApplication::UnicodeUTF8));
        setNGearButton->setText(QApplication::translate("MainWindow", "N", 0, QApplication::UnicodeUTF8));
        setDGearButton->setText(QApplication::translate("MainWindow", "D", 0, QApplication::UnicodeUTF8));
        label_nowGear->setText(QApplication::translate("MainWindow", "N", 0, QApplication::UnicodeUTF8));
        setRGearButton->setText(QApplication::translate("MainWindow", "R", 0, QApplication::UnicodeUTF8));
        setPGearButton->setText(QApplication::translate("MainWindow", "P", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "6->Park && Stop", 0, QApplication::UnicodeUTF8));
        pushButton_15->setText(QApplication::translate("MainWindow", "Press", 0, QApplication::UnicodeUTF8));
        pushButton_16->setText(QApplication::translate("MainWindow", "Release", 0, QApplication::UnicodeUTF8));
        pushButton_17->setText(QApplication::translate("MainWindow", "slow down to stop", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Speed(km/h):", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Battery(V):", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "engine:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "BrakeOpening:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "ThrottleOpening:", 0, QApplication::UnicodeUTF8));
        label_nowSpeed->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_nowBattery->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_nowEngine->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_nowBOpening->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_nowTOpening->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "ConnectStatus", 0, QApplication::UnicodeUTF8));
        label_connectStatus->setText(QApplication::translate("MainWindow", "offline", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("MainWindow", "\346\265\213\350\257\225\345\210\271\350\275\246\347\233\270\345\205\263\345\212\237\350\203\275", 0, QApplication::UnicodeUTF8));
        pushButton_18->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Copyright(c) 2018 CQJD XINGYUAN GROUP. All rights reserved. ", 0, QApplication::UnicodeUTF8));
        label_nowTime->setText(QApplication::translate("MainWindow", "now Time", 0, QApplication::UnicodeUTF8));
        groupBox_10->setTitle(QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "API test", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "fun2", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "fun3", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Page4", 0, QApplication::UnicodeUTF8));
        menuA->setTitle(QString());
        menuB->setTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
