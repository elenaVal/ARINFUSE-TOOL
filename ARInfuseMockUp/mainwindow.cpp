#include "mainwindow.h"

#include <iostream>

#include "settings_view.h"
#include "trainee_view.h"
#include "trainer_view.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(const std::string& default_tool_path,
                       const std::string& default_data_path) :
    ui_(new Ui::MainWindow()),

    settings_view_(
        new arinfuse::SettingsView(default_tool_path, default_data_path)),
    tool_runner_(new arinfuse::ToolRunner(settings_view_.get())),

    trainee_view_(
        new arinfuse::TraineeView(settings_view_.get(), tool_runner_.get())),
    trainer_view_(
        new arinfuse::TrainerView(settings_view_.get(), tool_runner_.get()))
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    ui_->setupUi(this);

    ui_->tool_path_text->setText(default_tool_path.c_str());
    ui_->data_path_text->setText(default_data_path.c_str());
}

void MainWindow::on_viewARBtn_clicked()
{
    viewARVR = new ViewARVR(this, settings_view_.get(), tool_runner_.get());
    viewARVR->show();
}

void MainWindow::on_gisViewBtn_clicked() {
  trainee_view_->RunGis();
}

void MainWindow::on_xml_processor_btn_clicked() {
  trainer_view_->RunXmlProccessor();
}

void MainWindow::on_camera_calibration_btn_clicked() {
  trainer_view_->RunCameraCalibration();
}

void MainWindow::on_pose_estimation_btn_clicked() {
  trainer_view_->RunPoseEstimation();
}

void MainWindow::on_data_path_btn_clicked() {
  settings_view_->UpdateDataPath(
      ui_->data_path_text->displayText().toStdString());
}

void MainWindow::on_tool_path_btn_clicked() {
  settings_view_->UpdateToolPath(
      ui_->tool_path_text->displayText().toStdString());
}
