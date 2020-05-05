#include "viewarvr.h"

#include <functional>

#include <QPixmap>

#include "configuration.h"

#include "ui_viewarvr.h"


namespace {

const char kLaraTool[] = "LARABuild/LARA.exe";

}  // namespace

ViewARVR::ViewARVR(QWidget *parent, arinfuse::Configuration* configuration, arinfuse::ToolRunner* tool_runner) :
    QDialog(parent),
    ui_(new Ui::ViewARVR()),
    configuration_(configuration),
    tool_runner_(tool_runner) {
  ui_->setupUi(this);
}

//With the click of the button
//The AR module is executed which
//Creates the AR image. This image
//is the displayed to the user.
// **Note** (May need to change the size of the image)
void ViewARVR::on_showImage_clicked() {
  ShowImage(ui_->label_pic, arinfuse::Configuration::kInputImageFile);
  runLARAapp();
}

template <class T>
void ViewARVR::ShowImage(T* label, const std::string& image) {
  QPixmap pix(configuration_->GetDataFilePath(image).c_str());
  int width = label->width();
  int height = label->height();
  label->setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
}

void ViewARVR::OnRendererProccessExit(int exit_code,
                                      QProcess::ExitStatus exit_status) {
  ShowImage(ui_->label_normal, arinfuse::Configuration::kAugmentedImageFile);
}

bool ViewARVR::runLARAapp() {
  return tool_runner_->RunTool(
      kLaraTool,
      {"-in_xml",
       configuration_->GetDataFilePath(
           arinfuse::Configuration::kPreprocessedXmlFile),
       "-in_image",
       configuration_->GetDataFilePath(
           arinfuse::Configuration::kInputImageFile),
       "-in_pose",
       configuration_->GetDataFilePath(
           arinfuse::Configuration::kCameraPoseFile),
       "-in_params",
       configuration_->GetDataFilePath(
           arinfuse::Configuration::kCameraCalibrationFile),
       "-in_cammins",
       configuration_->GetDataFilePath(
           arinfuse::Configuration::kCameraPositionOffsetFile),
       "-AugmentedImage",
       configuration_->GetDataFilePath(
           arinfuse::Configuration::kAugmentedImageFile),
       "-DepthPass",
       configuration_->GetDataFilePath(arinfuse::Configuration::kDepthPassFile),
       "-IdPass",
       configuration_->GetDataFilePath(arinfuse::Configuration::kIdPassFile),
       "-UnityOutput",
       configuration_->GetDataFilePath(
           arinfuse::Configuration::kUnityOutputFile)},
      std::bind(&ViewARVR::OnRendererProccessExit, this, std::placeholders::_1,
                std::placeholders::_2));
}

