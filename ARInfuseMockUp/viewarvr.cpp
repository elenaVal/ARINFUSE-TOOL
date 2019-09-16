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

//With the click of the button
//The AR module is executed which
//Creates the AR image. This image
//is the displayed to the user.
// **Note** (May need to change the size of the image)
void ViewARVR::on_showImage_clicked()
{
    runLARAapp();
    showARImage();
    showNormalImage();
}

void ViewARVR::showARImage()
{
    QPixmap pix("../LARABuild/Data/image_augmented.jpg");
    int width = ui->label_pic->width();
    int height = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(width,height,Qt::KeepAspectRatio));
}

void ViewARVR::showNormalImage()
{
    QPixmap pix("../LARABuild/Data/Pos5_undistorted.jpg");
    int width = ui->label_normal->width();
    int height = ui->label_normal->height();
    ui->label_normal->setPixmap(pix.scaled(width,height,Qt::KeepAspectRatio));
}

void ViewARVR::runLARAapp()
{
    QString path_to_exe = "../LARABuild/LARA.exe";
    QStringList arg_list;
    arg_list << "-popupwindow" << "-in_xml" << "../LARABuild/Data/preprocessed.xml" << "-in_image" << "../LARABuild/Data/Pos5_undistorted.jpg"
             << "-in_pose" << "../LARABuild/Data/pose_ar.txt" << "-in_params" << "../LARABuild/Data/params_ar.txt" << "-in_cammins" << "../LARABuild/Data/camera_mins.txt"
             << "-AugmentedImage" << "../LARABuild/Data/image_augmented.jpg" << "-DepthPass" << "../LARABuild/Data/image_depth.pam" << "-IdPass ../LARABuild/Data/image_ID.jpg"
             << "-UnityOutput" << "../LARABuild/Data/unity_output.txt";
    QProcess::execute(path_to_exe, arg_list);
}

