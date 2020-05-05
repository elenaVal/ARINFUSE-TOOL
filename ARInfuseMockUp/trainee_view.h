#ifndef ARINFUSE_TRAINEE_VIEW_H_
#define ARINFUSE_TRAINEE_VIEW_H_

#include "configuration.h"
#include "tool_runner.h"

namespace arinfuse {

// Encapsulates functions of the trainee tab.
class TraineeView {
 public:
  TraineeView(arinfuse::Configuration* configuration,
              arinfuse::ToolRunner* tool_runner);

  bool RunGis();
  bool RunAR();

 private:
  arinfuse::Configuration* configuration_;
  arinfuse::ToolRunner* tool_runner_;
};

}  // namespace arinfuse

#endif // ARINFUSE_TRAINEE_VIEW_H_
