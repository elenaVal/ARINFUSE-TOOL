#include "tool_runner.h"

#include <functional>
#include <sstream>

#include <QDebug>
#include <QProcess>

namespace arinfuse {
namespace {

void DoNothing(int, QProcess::ExitStatus) {
  // Intentionally empty.
}

} // namespace

ToolRunner::ToolRunner(arinfuse::Configuration* configuration)
    : configuration_(configuration) {}

ToolRunner::~ToolRunner() {
  // TODO(yannic): Stop leaking the process.
  subprocess_.release();
}

bool ToolRunner::RunTool(
    const std::string& tool, const std::vector<std::string>& args) {
  return Run(configuration_->GetToolPath(tool), args, DoNothing);
}

bool ToolRunner::RunTool(const std::string &tool,
                         const std::vector<std::string> &args,
                         ToolRunner::ProccessExitCallback callback) {
  return Run(configuration_->GetToolPath(tool), args, std::move(callback));
}

bool ToolRunner::Run(
    const std::string& executable, const std::vector<std::string>& args) {
  return Run(executable, args, "", DoNothing);
}

bool ToolRunner::Run(const std::string &executable,
                     const std::vector<std::string> &args,
                     ToolRunner::ProccessExitCallback callback) {
  return Run(executable, args, "", std::move(callback));
}

bool ToolRunner::Run(
    const std::string& executable,
    const std::vector<std::string>& args,
    const std::string& working_directory) {
  return Run(executable, args, working_directory, DoNothing);
}

bool ToolRunner::Run(const std::string &executable,
                     const std::vector<std::string> &args,
                     const std::string &working_directory,
                     ToolRunner::ProccessExitCallback callback) {
  if (subprocess_) {
    // TODO(yannic): Stop leaking the process.
    subprocess_.release();
  }
  subprocess_.reset(new QProcess());

  subprocess_->connect(
      subprocess_.get(),
      static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(
          &QProcess::finished),
      std::move(callback));

  if ("" != working_directory) {
    subprocess_->setWorkingDirectory(working_directory.c_str());
  }

  std::stringstream cmd;
  cmd << executable;
  for (const std::string &arg : args) {
    cmd << ' ' << arg;
  }

  subprocess_->start(cmd.str().c_str());
  switch (subprocess_->state()) {
  case QProcess::ProcessState::Running: // Fallthrough.
  case QProcess::ProcessState::Starting:
    // Success.
    return true;

  default:
    // Process failed to start.
    qDebug() << subprocess_->state();
    return false;
  }
}

}  // namespace arinfuse
