// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#include "arinfuse/pose_estimation/pose_estimation_window.h"

#include "opencv2/core.hpp"
#include "opencv2/core/eigen.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv_utils/opencv_image_viewer.h"

namespace dfki_av {
namespace arinfuse {
namespace {

template <typename Point>
void DrawPoint(cv::Mat& image, const Point& point, const cv::Scalar& color) {
  cv::circle(image, point, 10, color, -1);
}

void DrawPoints(
    cv::Mat& image,
    const std::vector<cv::Point2i>& points,
    const cv::Scalar& color) {
  for (const cv::Point2i& point : points) {
    DrawPoint(image, point, color);
  }
}

}  // namespace

PoseEstimationWindow::PoseEstimationWindow(
    PoseEstimation* pose_estimation, const cv::Mat& image)
    : dfki_av::tools::OpenCVImageViewer("arinfuse_pose_estimation"),
      pose_estimation_(pose_estimation),
      image_(image) {
  DrawImage(image_);
}

PoseEstimationWindow::~PoseEstimationWindow() = default;

void PoseEstimationWindow::Reset() {
  // 1. Reset all internal state.
  pose_estimation_->Reset();
  points_.clear();

  // 2. Update UI.
  DrawImage(image_);
}

void PoseEstimationWindow::MouseCallback(int event, int x, int y, int flags) {
  if (event != cv::EVENT_LBUTTONDOWN) {
    return;
  }

  cv::Point2i mouse_position(x, y);

  // 1. Create copy of image for drawing.
  cv::Mat image;
  image_.copyTo(image);

  // 2. Add new correspondence.
  points_.push_back(mouse_position);
  pose_estimation_->AddCorrespondence(mouse_position);

  // 3. Draw current state into |image|.
  DrawPoints(image, points_, cv::Scalar(0, 255, 0));

  // 4. Show |image| to user.
  DrawImage(image);
}

void PoseEstimationWindow::ReprojectWorldPoints(
    const std::vector<cv::Point3d>& world_points,
    const Eigen::Matrix3d& camera_calibration,
    const Eigen::Matrix4d& pose) {
  cv::Mat opencv_pose;
  cv::eigen2cv(pose, opencv_pose);

  Eigen::Matrix3d R;
  Eigen::Vector3d t;
  cv::cv2eigen(opencv_pose.rowRange(0, 3).colRange(0, 3), R);
  cv::cv2eigen(opencv_pose.rowRange(0, 3).col(3), t);

  // 1. Create copy of image for drawing.
  cv::Mat image;
  image_.copyTo(image);

  // 2. Draw current state into |image|.
  DrawPoints(image, points_, cv::Scalar(0, 255, 0));

  // 3. Reproject world points into image.
  for (const cv::Point3d& world_point : world_points) {
    Eigen::Vector3d point(world_point.x, world_point.y, world_point.z);

    Eigen::Vector3d projected_point = camera_calibration * ((R * point) + t);
    cv::Point2d image_point(
        (projected_point(0) / projected_point(2)),
        (projected_point(1) / projected_point(2)));
    DrawPoint(image, image_point, cv::Scalar(0, 0, 255));
  }

  // 4. Show |image| to user.
  DrawImage(image);
}

}  // namespace arinfuse
}  // namespace dfki_av
