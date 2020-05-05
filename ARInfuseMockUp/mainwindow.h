#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "viewarvr.h"

#include <memory>

#include <QMainWindow>

#include "settings_view.h"
#include "tool_runner.h"
#include "trainee_view.h"
#include "trainer_view.h"

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(
      const std::string& default_tool_path,
      const std::string& default_data_path);

 private slots:
  // Trainee view.
  void on_viewARBtn_clicked();
  void on_gisViewBtn_clicked();

  // Trainee view.
  void on_xml_processor_btn_clicked();
  void on_camera_calibration_btn_clicked();
  void on_pose_estimation_btn_clicked();

  // Trainee view.
  void on_data_path_btn_clicked();
  void on_tool_path_btn_clicked();

 private:
  std::unique_ptr<Ui::MainWindow> ui_;

    ViewARVR *viewARVR;

  std::unique_ptr<arinfuse::SettingsView> settings_view_;
  std::unique_ptr<arinfuse::ToolRunner> tool_runner_;

  std::unique_ptr<arinfuse::TraineeView> trainee_view_;
  std::unique_ptr<arinfuse::TrainerView> trainer_view_;
};

#endif // MAINWINDOW_H
