// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#ifndef ARINFUSE_CAMERA_CALIBRATION_CALIBRATION_WINDOW_H_
#define ARINFUSE_CAMERA_CALIBRATION_CALIBRATION_WINDOW_H_

#include <utility>
#include <vector>

#include "arinfuse/camera_calibration/vanishing_points_calibration.h"
#include "opencv2/core.hpp"
#include "opencv_utils/opencv_image_viewer.h"

namespace dfki_av {
namespace arinfuse {

class CalibrationWindow : public dfki_av::tools::OpenCVImageViewer {
 public:
  CalibrationWindow(
      VanishingPointsCalibration* vanishing_points_calibration,
      const cv::Mat& image);
  ~CalibrationWindow();

  void Reset();

 private:
  // dfki_av::tools::OpenCVImageViewer overrides.
  void MouseCallback(int event, int x, int y, int flags) override;

  VanishingPointsCalibration* vanishing_points_calibration_;
  cv::Mat image_;

  cv::Point2i current_mouse_anchor_;
  std::pair<cv::Point2i, cv::Point2i> current_first_line_;

  std::vector<std::pair<cv::Point2i, cv::Point2i>> lines_;
};

}  // namespace arinfuse
}  // namespace dfki_av

#endif  // ARINFUSE_CAMERA_CALIBRATION_CALIBRATION_WINDOW_H_
