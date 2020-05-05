// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#include "arinfuse/camera_calibration/calibration_window.h"

#include <iostream>
#include <utility>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv_utils/opencv_image_viewer.h"

namespace dfki_av {
namespace arinfuse {
namespace {

cv::Point2i UninitializedPoint() {
  return cv::Point2i(-1, -1);
}

std::pair<cv::Point2i, cv::Point2i> UninitializedLine() {
  return std::make_pair<cv::Point2i, cv::Point2i>(
      UninitializedPoint(), UninitializedPoint());
}

bool IsInitialized(const cv::Point2i& point) {
  return (-1 != point.x && -1 != point.y);
}

bool IsInitialized(const std::pair<cv::Point2i, cv::Point2i>& line) {
  return IsInitialized(line.first) && IsInitialized(line.second);
}

void DrawLine(
    cv::Mat& image, const cv::Point2i& first, const cv::Point2i& second) {
  // TODO(yannic): Should we draw line of infinite length here?
  cv::line(
      image,
      cv::Point2i(
          first.x + (image.size().width / 2),
          (image.size().height / 2) - first.y),
      cv::Point2i(
          second.x + (image.size().width / 2),
          (image.size().height / 2) - second.y),
      /* color= */ cv::Scalar(/* blue= */ 0, /* green= */ 255, /* red= */ 0),
      /* thickness= */ 2);
}

cv::Point2d GetIntersection(
    const cv::Point2d& p1,
    const cv::Point2d& p2,
    const cv::Point2d& p3,
    const cv::Point2d& p4) {
  // https://en.wikipedia.org/wiki/Line–line_intersection#Given_two_points_on_each_line
  double x =
      ((((p1.x * p2.y) - (p2.x * p1.y)) * (p3.x - p4.x)) -
       ((p1.x - p2.x) * ((p3.x * p4.y) - (p4.x * p3.y)))) /
      (((p1.x - p2.x) * (p3.y - p4.y)) - ((p1.y - p2.y) * (p3.x - p4.x)));
  double y =
      ((((p1.x * p2.y) - (p2.x * p1.y)) * (p3.y - p4.y)) -
       ((p1.y - p2.y) * ((p3.x * p4.y) - (p4.x * p3.y)))) /
      (((p1.x - p2.x) * (p3.y - p4.y)) - ((p1.y - p2.y) * (p3.x - p4.x)));
  return cv::Point2d(x, y);
}

// Computes the intersection point between |line1| and |line2|, and returns
// whether such a point exists.
cv::Point2i GetIntersection(
    const std::pair<cv::Point2i, cv::Point2i>& line1,
    const std::pair<cv::Point2i, cv::Point2i>& line2) {
  cv::Point2d intersection =
      GetIntersection(line1.first, line1.second, line2.first, line2.second);
  return cv::Point2i((int)intersection.x, ((int)intersection.y));
}

}  // namespace

CalibrationWindow::CalibrationWindow(
    VanishingPointsCalibration* vanishing_points_calibration,
    const cv::Mat& image)
    : dfki_av::tools::OpenCVImageViewer("arinfuse_camera_calib"),
      vanishing_points_calibration_(vanishing_points_calibration),
      image_(image),
      current_mouse_anchor_(UninitializedPoint()),
      current_first_line_(UninitializedLine()) {
  DrawImage(image_);
}

CalibrationWindow::~CalibrationWindow() = default;

void CalibrationWindow::Reset() {
  // 1. Reset all internal state.
  vanishing_points_calibration_->Reset();
  current_mouse_anchor_ = UninitializedPoint();
  current_first_line_ = UninitializedLine();
  lines_.clear();

  // 2. Update UI.
  DrawImage(image_);
}

void CalibrationWindow::MouseCallback(int event, int x, int y, int flags) {
  cv::Point2i mouse_position(
      x - (image_.size().width / 2), -(y - (image_.size().height / 2)));

  // 1. Create copy of image for drawing.
  cv::Mat image;
  image_.copyTo(image);

  // 2. React to mouse event.
  switch (event) {
    case cv::EVENT_RBUTTONDOWN:
      // The user pressed the right mouse button, abort current operation.
      if (IsInitialized(current_mouse_anchor_)) {
        // The user is drawing a line, only abort the current line.
        current_mouse_anchor_ = UninitializedPoint();
      } else if (IsInitialized(current_first_line_)) {
        // The user pressed when not drawing a line, abort pair of lines.
        current_first_line_ = UninitializedLine();
      }
      break;

    case cv::EVENT_LBUTTONDOWN:
      if (!IsInitialized(current_mouse_anchor_)) {
        // This is the first of two points defining a line.
        current_mouse_anchor_ = mouse_position;
      } else {
        // This is the second of two points defining a line.
        auto current_line = std::make_pair<cv::Point2i, cv::Point2i>(
            std::move(current_mouse_anchor_), std::move(mouse_position));
        current_mouse_anchor_ = UninitializedPoint();

        if (IsInitialized(current_first_line_)) {
          // We have a pair of lines to compute the vanishing point.
          std::pair<cv::Point2i, cv::Point2i> first_line = current_first_line_;
          current_first_line_ = UninitializedLine();

          lines_.push_back(first_line);
          lines_.push_back(current_line);

          vanishing_points_calibration_->AddVanishingPoint(
              GetIntersection(first_line, current_line));
        } else {
          // We drew only the first line, save it for later.
          current_first_line_ = current_line;
        }
      }
      break;

    default:
      if (IsInitialized(current_first_line_)) {
        DrawLine(image, current_first_line_.first, current_first_line_.second);
      }

      if (IsInitialized(current_mouse_anchor_)) {
        DrawLine(image, current_mouse_anchor_, mouse_position);
      }
      break;
  }

  // 3. Draw current state into |image|.
  for (const std::pair<cv::Point2i, cv::Point2i> line : lines_) {
    DrawLine(image, line.first, line.second);
  }

  // 4. Show |image| to user.
  DrawImage(image);
}

}  // namespace arinfuse
}  // namespace dfki_av
