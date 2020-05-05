// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#ifndef ARINFUSE_POSE_ESTIMATION_POSE_ESTIMATION_H_
#define ARINFUSE_POSE_ESTIMATION_POSE_ESTIMATION_H_

#include <vector>

#include "Eigen/Eigen"
#include "opencv2/core.hpp"

namespace dfki_av {
namespace arinfuse {

class PoseEstimation {
 public:
  PoseEstimation(
      const std::vector<cv::Point3d>& world_points,
      const Eigen::Matrix3d& camera_calibration);
  ~PoseEstimation();

  void AddCorrespondence(const cv::Point2d& image_point);

  void Reset();

  Eigen::Matrix4d EstimatePose() const;

 private:
  // List of correspondences between world-points and image-points.
  std::vector<cv::Point3d> world_points_;
  std::vector<cv::Point2d> image_points_;

  Eigen::Matrix3d camera_calibration_;
};

}  // namespace arinfuse
}  // namespace dfki_av

#endif  // ARINFUSE_POSE_ESTIMATION_POSE_ESTIMATION_H_
