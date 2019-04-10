#include "viewarvr.h"
#include "ui_viewarvr.h"
#include <QPixmap>

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

void ViewARVR::on_showImage_clicked()
{
    QPixmap pix("E:/LARABuild/Data/image_augmented.jpg");
    int width = ui->label_pic->width();
    int height = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(width,height,Qt::KeepAspectRatio));
}
