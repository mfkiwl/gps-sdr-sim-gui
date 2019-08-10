#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QString>
#include <QDir>
#include <time.h>
#include <iostream>
#include <QFileDialog>
#include <string>
#include <sstream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{    QDir::setCurrent("/home/sasha/Desktop/MAN/gps-sdr-sim");
    QProcess process1;
    process1.start("bash getbrdc.sh");
    process1.waitForFinished();
    QString output = process1.readAllStandardError();
    QMessageBox::information(0,"12",output);
    if (ui->radioButton->isChecked()) {

       QString a=(ui->lineEdit->text());
       float x=a.toFloat();
       QString b=(ui->lineEdit_2->text());
       float y=b.toFloat();
       QString c=(ui->lineEdit_3->text());
       float z=c.toFloat();
        QProcess process2;
        QStringList arguments;
        int tm_yday;

        QString convert= QString::number(tm_yday);

        arguments <<" -e "<<"brdc"<<convert<<"0.18n"<< " -l " << a << "," << b <<","<<c<<" -T "<<(ui->lineEdit_9->text())<<" "<<(ui->lineEdit_10->text());
        process2.start("bash gps-sgr-sim",arguments);
        process2.waitForFinished();
    } else{
        QProcess process3;
         QString filename = QFileDialog::getOpenFileName(this,tr("Specify .csv file"));
        QStringList arguments12;
        int tm_yday;
        QString convert= QString::number(tm_yday);
        arguments12 <<" -e "<<"brdc"<<convert<<"0.18n"<< " -u " << filename << " -T "<<(ui->lineEdit_9->text())<<" "<<(ui->lineEdit_10->text());
        process3.start("bash gps-sgr-sim",arguments12);
        process3.waitForFinished();
    }

    if (ui->checkBox->checkState()) {

        QProcess process4;
        process4.start("python top_block.py");
        process4.waitForFinished();
        QProcess process5;
        QStringList arguments1;
        arguments1<<" -t gpssim1.bin -f 1575420000 -s 2600000 -a 1 -x 0";
        process5.start("hackrf_transfer",arguments1);
        process5.waitForFinished();
    }   else {
        QProcess process5;
        QStringList arguments2;
        arguments2<<" -t gpssim.bin -f 1575420000 -s 2600000 -a 1 -x 0";
        process5.start("hackrf_transfer",arguments2);
        process5.waitForFinished();

                   }
}


