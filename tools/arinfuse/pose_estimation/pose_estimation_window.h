// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#ifndef ARINFUSE_POSE_ESTIMATION_POSE_ESTIMATION_WINDOW_H_
#define ARINFUSE_POSE_ESTIMATION_POSE_ESTIMATION_WINDOW_H_

#include <vector>

#include "Eigen/Eigen"
#include "arinfuse/pose_estimation/pose_estimation.h"
#include "opencv2/core.hpp"
#include "opencv_utils/opencv_image_viewer.h"

namespace dfki_av {
namespace arinfuse {

class PoseEstimationWindow : public dfki_av::tools::OpenCVImageViewer {
 public:
  PoseEstimationWindow(PoseEstimation* pose_estimation, const cv::Mat& image);
  ~PoseEstimationWindow();

  void Reset();

  void ReprojectWorldPoints(
      const std::vector<cv::Point3d>& world_points,
      const Eigen::Matrix3d& camera_calibration,
      const Eigen::Matrix4d& pose);

 private:
  // dfki_av::tools::OpenCVImageViewer overrides.
  void MouseCallback(int event, int x, int y, int flags) override;

  PoseEstimation* pose_estimation_;
  cv::Mat image_;

  std::vector<cv::Point2i> points_;
};

}  // namespace arinfuse
}  // namespace dfki_av

#endif  // ARINFUSE_POSE_ESTIMATION_POSE_ESTIMATION_WINDOW_H_
