#ifndef ARINFUSE_TOOL_RUNNER_H_
#define ARINFUSE_TOOL_RUNNER_H_

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <QProcess>

#include "configuration.h"

namespace arinfuse {

// Encapsulates functions to run external tools.
class ToolRunner {
 public:
   using ProccessExitCallback = std::function<void(int, QProcess::ExitStatus)>;

   ToolRunner(arinfuse::Configuration *configuration);
   ~ToolRunner();

   bool RunTool(const std::string &tool, const std::vector<std::string> &args);
   bool RunTool(const std::string &tool, const std::vector<std::string> &args,
                ProccessExitCallback callback);
   bool Run(const std::string &executable,
            const std::vector<std::string> &args);
   bool Run(const std::string &executable, const std::vector<std::string> &args,
            ProccessExitCallback callback);
   bool Run(const std::string &executable, const std::vector<std::string> &args,
            const std::string &working_directory);
   bool Run(const std::string &executable, const std::vector<std::string> &args,
            const std::string &working_directory,
            ProccessExitCallback callback);

 private:
  arinfuse::Configuration* configuration_;

  std::unique_ptr<QProcess> subprocess_;
};

}  // namespace arinfuse

#endif // ARINFUSE_TOOL_RUNNER_H_
