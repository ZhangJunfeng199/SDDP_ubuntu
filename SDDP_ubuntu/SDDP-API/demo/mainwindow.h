#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QTimer>
#include "sddp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_self_button_clicked();
    void statusTimerUpDate();
    void sysDataTimerUpDate();

    void on_manual_button_clicked();

    void on_pushButton_clicked();

    void on_steerEnableButton_clicked();

    void on_InitSButton_clicked();

    void on_unintServiceButton_clicked();

    void on_steerDisableButton_clicked();

    void on_steerAddButton_clicked();

    void on_steerSubButton_clicked();

    void on_steerSetButton_clicked();

    void on_setNGearButton_clicked();

    void on_setDGearButton_clicked();

    void on_setRGearButton_clicked();

    void on_setPGearButton_clicked();

    void on_pushButton_18_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *status_timer;   //0.5s
    QTimer *sysData_timer;  //0.1s
    int nowTime;
    double nowSteer;
    double nowAcc;
    //sddp
    SddpOperator* sdk;
};

#endif // MAINWINDOW_H
