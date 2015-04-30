#include "xtools.h"
#include "ui_xtools.h"
#include <iostream>
#include <stdlib.h>
#include <QApplication>
#include <QComboBox>
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QProcess>
#include <QProgressDialog>
QProcess process;

XTools::XTools(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::XTools)
{
    ui->setupUi(this);
    system("adb start-server");
}

XTools::~XTools()
{
    delete ui;
}

void XTools::on_Load_clicked()
{
    // TOFIX
    system("adb start-server");
    QString device = system("adb shell getprop ro.product.model"),
            status = system("adb get-state"),
            serial = system("adb get-serialno"),
            abuild = system("adb shell getprop ro.build.version.release");
    ui->deviceL->setText(device);
    ui->StatusL->setText(status);
    ui->SerialL->setText(serial);
    ui->AndroidL->setText(abuild);
}

/**
 * Actions
 */


void XTools::on_actionReload_triggered()
{
    XTools::on_Load_clicked();
}

void XTools::on_actionAbout_triggered()
{
    QMessageBox::about(this,tr("About XiaomiTool"),"©2015 Joey Rizzoli (@linuxx)\nSources: https://github.com/linuxxxxx/XTools\nXiaomiTools is an opensource software that has the goal to provide a fast, safe and user friendly tool to manage your Xiaomi Device.");
}

void XTools::on_actionExit_triggered()
{
    delete ui;
}

/**
 * Manage
 */

void XTools::on_Backup_clicked()
{
    QString file = QFileDialog::getSaveFileName(this, tr("Save backup"), "", ".ab;;All files (*.*)");
    const char *backupfile = qPrintable(file);
    setenv("backupfile", backupfile, true);
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb backup -apk -nosystem -noshared f $backupfile; sleep 1");
    dialog->exec();
    QMessageBox::information(this,tr("Backup"),"Done!","OK");
}

void XTools::on_Restore_clicked()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Choose backup"),"~","Backups (*.ab);;All files (*.*)");
    const char *backupfile = qPrintable(file);
    setenv("backupfile", backupfile, true);
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb restore $backupfile; sleep 1");
    dialog->exec();
    QMessageBox::information(this,tr("Restore Backup"),"Done!","OK");
}

void XTools::on_ScreenShot_clicked()
{
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute((Qt::WA_DeleteOnClose));
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("bash :/tools/res/scripts/screenshot.sh");
    dialog->exec();
    QMessageBox::information(this,tr("Screenshot"),"Done!","OK");
}

void XTools::on_ApkI_clicked()
{
    QString apk=QFileDialog::getOpenFileName(this, tr("Choose File"), "~", "Apk files (*.apk);;All Files (*.*)");
    const char *fapk = qPrintable(apk);
    setenv("fapk", fapk, true);
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
   connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
   process.start("adb install $fapk");
   dialog->exec();
   QMessageBox::information(this,tr("Apk Installer"),"Done!","OK");
}

void XTools::on_Push_clicked()
{
    QString pushfile=QFileDialog::getOpenFileName(this, tr("Choose File"), "~", "All Files (*.*)");
    const char *file = qPrintable(pushfile);
    setenv("pushfile", file, true);
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb push $pushfile /sdcard/");
    dialog->exec();
    QMessageBox::information(this,tr("Push File"),"Done!","OK");
}

void XTools::on_PushF_clicked()
{
    QString pushfile=QFileDialog::getExistingDirectory(this, tr("Choose directory"), "~");
    const char *file = qPrintable(pushfile);
    setenv("pushfile", file, true);
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb push $pushfile /sdcard/");
    dialog->exec();
    QMessageBox::information(this,tr("Push Directory"),"Done!","OK");

}

void XTools::on_PushS_clicked()
{
    QString pushfile=QFileDialog::getOpenFileName(this, tr("Choose song"), "~", "All Files (*.*)");
    const char *file = qPrintable(pushfile);
    setenv("pushfile", file, true);
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb push $pushfile /sdcard/Music/");
    dialog->exec();
    QMessageBox::information(this,tr("Push Song"),"Done!","OK");
}


void XTools::on_PushP_clicked()
{
    QString pushfile=QFileDialog::getOpenFileName(this, tr("Choose picture"), "~", "All Files (*.*)");
    const char *file = qPrintable(pushfile);
    setenv("pushfile", file, true);
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb push $pushfile /sdcard/Pictures/");
    dialog->exec();
    QMessageBox::information(this,tr("Push Picture"),"Done!","OK");

}

void XTools::on_PullP_clicked()
{
    QString camdir=QFileDialog::getExistingDirectory(this,tr("Choose the destination folder"), "~");
    const char *out = qPrintable(camdir);
    setenv("camdir", out, true);
    QProcess process;
    QProgressDialog *dialog = new QProgressDialog;
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->setRange(0,0);
    connect(&process, SIGNAL(finished(int)), dialog, SLOT(close()));
    process.start("adb pull /sdcard/DCIM/Camera $camdir");
    dialog->exec();
    QMessageBox::information(this,tr("Import from camera"),"Done!","OK");
}
