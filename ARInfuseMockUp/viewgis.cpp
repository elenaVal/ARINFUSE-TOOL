#include "viewgis.h"
#include "ui_viewgis.h"

viewGIS::viewGIS(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewGIS)
{
    ui->setupUi(this);
}

viewGIS::~viewGIS()
{
    delete ui;
}
