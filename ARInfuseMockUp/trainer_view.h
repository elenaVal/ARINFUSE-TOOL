#ifndef ARINFUSE_TRAINER_VIEW_H_
#define ARINFUSE_TRAINER_VIEW_H_

#include "configuration.h"
#include "tool_runner.h"

namespace arinfuse {

// Encapsulates functions of the trainer tab.
class TrainerView {
 public:
  TrainerView(arinfuse::Configuration* configuration,
              arinfuse::ToolRunner* tool_runner);

  bool RunXmlProccessor();
  bool RunCameraCalibration();
  bool RunPoseEstimation();

 private:
  arinfuse::Configuration* configuration_;
  arinfuse::ToolRunner* tool_runner_;
};

}  // namespace arinfuse

#endif // ARINFUSE_TRAINER_VIEW_H_
