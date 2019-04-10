#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>

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

void MainWindow::on_viewARBtn_clicked()
{
    viewARVR = new ViewARVR(this);
    viewARVR->show();
}

void MainWindow::on_gisViewBtn_clicked()
{
    gisProcess = new QProcess(this);
    //get the directory where the executable is (of the qt application, .exe)
    QString path = qApp->applicationDirPath();
    //set current working directory
    gisProcess->setWorkingDirectory(path);
    gisProcess -> start("java -jar gis-gis.jar");
    qDebug() << gisProcess->state();
    viewgis = new viewGIS(this);
}

void MainWindow::on_settingsBtn_clicked()
{
    settings = new Settings(this);
    settings->show();
}