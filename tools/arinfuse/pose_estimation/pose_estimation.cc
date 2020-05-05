// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#include "arinfuse/pose_estimation/pose_estimation.h"

#include "opencv2/calib3d.hpp"
#include "opencv2/core.hpp"
#include "opencv2/core/eigen.hpp"

namespace dfki_av {
namespace arinfuse {

PoseEstimation::PoseEstimation(
    const std::vector<cv::Point3d>& world_points,
    const Eigen::Matrix3d& camera_calibration)
    : world_points_(world_points), camera_calibration_(camera_calibration) {}

PoseEstimation::~PoseEstimation() = default;

void PoseEstimation::AddCorrespondence(const cv::Point2d& image_point) {
  image_points_.push_back(image_point);
}

void PoseEstimation::Reset() {
  image_points_.clear();
}

Eigen::Matrix4d PoseEstimation::EstimatePose() const {
  cv::Mat camera_calibration;
  cv::eigen2cv(camera_calibration_, camera_calibration);

  cv::Mat R;
  cv::Mat t;
  cv::solvePnP(
      world_points_, image_points_, camera_calibration,
      cv::Mat::zeros(4, 1, cv::DataType<double>::type), R, t);
  cv::Rodrigues(R, R);

  cv::Mat opencv_pose = cv::Mat::eye(4, 4, cv::DataType<double>::type);
  R.copyTo(opencv_pose.rowRange(0, 3).colRange(0, 3));
  t.copyTo(opencv_pose.rowRange(0, 3).col(3));

  Eigen::Matrix4d pose;
  cv::cv2eigen(opencv_pose, pose);
  return pose;
}

}  // namespace arinfuse
}  // namespace dfki_av
