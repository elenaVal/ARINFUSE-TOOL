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
   /* viewgis = new viewGIS(this);
    viewgis->show();*/

    gisProcess = new QProcess(this);
        //get the directory where the executable is (of the qt application, .exe)
    QString path = "E:/ANINFUSEMODULES/GIS-MODULE/GIS-MODULE/";
        //set current working directory
    gisProcess->setWorkingDirectory(path);
        //call the jar file
    gisProcess -> start("java -jar gis-gis.jar");
        //connect( gisProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(ReadOut()) );
     qDebug() << gisProcess->state();
     viewgis = new viewGIS(this);

}

void MainWindow::on_settingsBtn_clicked()
{
    settings = new Settings(this);
    settings->show();
}
