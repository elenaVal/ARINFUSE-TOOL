#include "viewarvr.h"
#include "ui_viewarvr.h"
#include <QPixmap>
#include <QProcess>

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
    QString path_to_exe = "E:/LARABuild/LARA.exe";
    QStringList arg_list;
    arg_list << "-popupwindow" << "-in_xml" << "E:/LARABuild/Data/preprocessed.xml" << "-in_image" << "E:/LARABuild/Data/Pos5_undistorted.jpg"
             << "-in_pose" << "E:/LARABuild/Data/pose_ar.txt" << "-in_params" << "E:/LARABuild/Data/params_ar.txt" << "-in_cammins" << "E:/LARABuild/Data/camera_mins.txt"
             << "-AugmentedImage" << "E:/LARABuild/Data/image_augmented.jpg" << "-DepthPass" << "E:/LARABuild/Data/image_depth.pam" << "-IdPass E:/LARABuild/Data/image_ID.jpg"
             << "-UnityOutput" << "E:/LARABuild/Data/unity_output.txt";
    QProcess::execute(path_to_exe, arg_list);

    QPixmap pix("E:/LARABuild/Data/image_augmented.jpg");
    int width = ui->label_pic->width();
    int height = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(width,height,Qt::KeepAspectRatio));
}
