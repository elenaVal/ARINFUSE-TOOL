#include "trainee_view.h"

#include <iostream>

namespace arinfuse {

TraineeView::TraineeView(arinfuse::Configuration* configuration,
                         arinfuse::ToolRunner* tool_runner)
    : configuration_(configuration), tool_runner_(tool_runner) {}

bool TraineeView::RunGis() {
  return tool_runner_->Run(
      "java",
      {"-jar", "gis-gis.jar"},
      configuration_->GetToolPath("GIS-MODULE/GIS-MODULE"));
}

bool TraineeView::RunAR() {
  std::cout << "TraineeView::RunAR()" << std::endl;
  return true;
}

}  // namespace arinfuse
