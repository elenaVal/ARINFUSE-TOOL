#include "viewarvr.h"
#include "ui_viewarvr.h"

ViewARVR::ViewARVR(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewARVR)
{
    ui->setupUi(this);
}

ViewARVR::~ViewARVR()
{
    delete ui;
}
