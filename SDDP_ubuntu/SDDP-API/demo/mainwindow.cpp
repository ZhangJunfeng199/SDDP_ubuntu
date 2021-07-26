#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "zmq/zmq.h"
#include "json/json.h"
#include "glog/logging.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    status_timer = new QTimer(this);
    sysData_timer = new QTimer(this);

    connect(status_timer,SIGNAL(timeout()),this,SLOT(statusTimerUpDate()));
        status_timer->start(500);

    connect(sysData_timer,SIGNAL(timeout()),this,SLOT(sysDataTimerUpDate()));
        sysData_timer->start(100);

     nowTime = 0;
     sdk = new SddpOperator();
     if (sdk == NULL) {
         perror("failed to create sddp sdk!\n");
         exit(1);
     }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_self_button_clicked()
{
    sdk->SetMode(SddpOperator::MD_SELF_DRIVING);
}


void MainWindow::statusTimerUpDate()
{
    QString str;
    //1.0
    //QDateTime time = QDateTime::currentDateTime();
    //1.1
    if (sdk->m_service_status == SddpOperator::SYS_UNINIT)
    {
        ui->label_connectStatus->setText("Offline");
    }
    else
    {
        switch (sdk->m_service_status)
        {
        case SddpOperator::SS_ONLINE:
            ui->label_connectStatus->setText("Online");
            break;
        case SddpOperator::SS_OFFLINE:
            ui->label_connectStatus->setText("Offline");
            break;
        case SddpOperator::SS_CONNECTING:
            ui->label_connectStatus->setText("Connecting");
        default:
            break;
        }
    }

    //1.2
    if(sdk->m_mode == SddpOperator::MD_MANUAL)
    {
        ui->label_mode->setText("Manual");
    }
    else if (sdk->m_mode == SddpOperator::MD_SELF_DRIVING)
    {
        ui->label_mode->setText("Self-driving");
    }
    //1.3
    if (sdk->m_steer_ctrl_enable)
    {
        ui->label_steerStatus->setText("Enable");
    }
    else
    {
        ui->label_steerStatus->setText("Disable");
    }
    //1.4
    if (sdk->m_acc_ctrl_enable)
    {
        ui->label_accStatus->setText("Enable");
    }
    else
    {
        ui->label_accStatus->setText("Disable");
    }
    //1.5
    switch(sdk->m_gear)
    {
    case SddpOperator::GEAR_D:
        ui->label_nowGear->setText("D");
        break;
    case SddpOperator::GEAR_N:
        ui->label_nowGear->setText("N");
        break;
    case SddpOperator::GEAR_P:
        ui->label_nowGear->setText("P");
        break;
    case SddpOperator::GEAR_R:
        ui->label_nowGear->setText("R");
        break;
    }
    //1.6
    switch (sdk->m_ems_engine_status)
    {
    case SddpOperator::ES_NORMAL:
        ui->label_nowEngine->setText("Normal");
        break;
    case SddpOperator::ES_FAULT:
        ui->label_nowEngine->setText("Fault");
        break;
    default:
        break;
    }
}

//0.1s
void MainWindow::sysDataTimerUpDate()
{
    QString str;
    ui->label_nowTime->setText("Current Time is:" +
                           QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
    //1.0
    str = QString::number(sdk->m_steer);
    ui->label_nowSteer->setText(str);
    //1.1
    str = QString::number(sdk->m_accelerate);
    ui->label_nowAcc->setText(str);
    //1.2
    str = QString::number(sdk->m_vdisplay);
    ui->label_nowSpeed->setText(str);
    //1.3
    str = QString::number(sdk->m_ems_battery_voltage);
    ui->label_nowBattery->setText(str);
    //1.4
    str = QString::number(sdk->m_brake);
    ui->label_nowBOpening->setText(str);
    //1.5
    str = QString::number(sdk->m_throte);
    ui->label_nowTOpening->setText(str);


}


void MainWindow::on_manual_button_clicked()
{
    sdk->SetMode(SddpOperator::MD_MANUAL);

}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_steerEnableButton_clicked()
{
    sdk->EnableSteerCtrl(true);
}

void MainWindow::on_InitSButton_clicked()
{
   if(sdk->InitService() == SDDP_OK)
   {
      LOG(INFO)<<"InitService OK";
   }
   else
   {
      LOG(INFO)<<"InitService failed!";
   }
}

void MainWindow::on_unintServiceButton_clicked()
{
    sdk->UninitService();
}

void MainWindow::on_steerDisableButton_clicked()
{
    sdk->EnableSteerCtrl(false);
}





void MainWindow::on_steerAddButton_clicked()
{
   sdk->OnSteerAdd();
}

void MainWindow::on_steerSubButton_clicked()
{
    sdk->OnSteerSub();
}

void MainWindow::on_steerSetButton_clicked()
{
    QString strObjSteer = ui->objSteer->text();
    double (objSteer) = strObjSteer.toDouble();
    if (objSteer >-720 && objSteer < 720)
    {
        sdk->SetSteering(objSteer);
    }
    else
    {
        LOG(ERROR)<<"objSteer input error!Please check objSteer";
    }
}

void MainWindow::on_setNGearButton_clicked()
{
    sdk->SetGear(SddpOperator::GEAR_N);
}

void MainWindow::on_setDGearButton_clicked()
{
    sdk->SetGear(SddpOperator::GEAR_D);
}

void MainWindow::on_setRGearButton_clicked()
{
    sdk->SetGear(SddpOperator::GEAR_R);
}
void MainWindow::on_setPGearButton_clicked()
{
    sdk->SetGear(SddpOperator::GEAR_P);
}

void MainWindow::on_pushButton_18_clicked()
{
     this->close();
}
