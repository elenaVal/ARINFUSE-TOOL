#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    viewgis = new viewGIS(this);
    viewgis->show();
}

void MainWindow::on_settingsBtn_clicked()
{
    settings = new Settings(this);
    settings->show();
}
