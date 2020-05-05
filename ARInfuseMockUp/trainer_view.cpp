#include "trainer_view.h"

#include <iostream>
#include <sstream>

#include <QDebug>
#include <QProcess>

namespace arinfuse {
namespace {

const char kXmlProccessorTool[] =
    "xml_preproccessor/xml_preproccessor.exe";
const char kCameraCalibrationTool[] =
    "camera_calibration/camera_calibration.exe";
const char kPoseEstimationTool[] =
    "pose_estimation/pose_estimation.exe";

}  // namespace

TrainerView::TrainerView(arinfuse::Configuration* configuration,
                         arinfuse::ToolRunner* tool_runner)
    : configuration_(configuration), tool_runner_(tool_runner) {}

bool TrainerView::RunXmlProccessor() {
  return tool_runner_->RunTool(
      kXmlProccessorTool,
      {"-i",
       configuration_->GetDataFilePath(arinfuse::Configuration::kRawXmlFile),
       "-c",
       configuration_->GetDataFilePath(
           arinfuse::Configuration::kCameraPositionOffsetFile),
       "-o",
       configuration_->GetDataFilePath(
           arinfuse::Configuration::kPreprocessedXmlFile)});
}

bool TrainerView::RunCameraCalibration() {
  return tool_runner_->RunTool(
      kCameraCalibrationTool,
      {configuration_->GetDataFilePath(
           arinfuse::Configuration::kInputImageFile),
       configuration_->GetDataFilePath(Configuration::kCameraCalibrationFile)});
}

bool TrainerView::RunPoseEstimation() {
  return tool_runner_->RunTool(
      kPoseEstimationTool,
      {configuration_->GetDataFilePath(
           arinfuse::Configuration::kInputImageFile),
       configuration_->GetDataFilePath(
           arinfuse::Configuration::kCameraCalibrationFile),
       configuration_->GetDataFilePath(
           arinfuse::Configuration::kWorldPointsFile),
       configuration_->GetDataFilePath(
           arinfuse::Configuration::kCameraPositionOffsetFile),
       configuration_->GetDataFilePath(Configuration::kCameraPoseFile)});
}

}  // namespace arinfuse
