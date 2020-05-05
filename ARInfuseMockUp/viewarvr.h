#ifndef VIEWARVR_H
#define VIEWARVR_H

#include <memory>
#include <string>

#include <QDialog>
#include <QProcess>

#include "configuration.h"
#include "tool_runner.h"

#include "ui_viewarvr.h"

class ViewARVR : public QDialog {
  Q_OBJECT

 public:
  explicit ViewARVR(QWidget* parent_window, arinfuse::Configuration* configuration, arinfuse::ToolRunner* tool_runner);

 private slots:
  void on_showImage_clicked();

 private:
  template <class T>
  void ShowImage(T* label, const std::string& image);

  void OnRendererProccessExit(int exit_code, QProcess::ExitStatus exit_status);

  bool runLARAapp();

  std::unique_ptr<Ui::ViewARVR> ui_;

  arinfuse::Configuration* configuration_;
  arinfuse::ToolRunner* tool_runner_;
};

#endif // VIEWARVR_H
