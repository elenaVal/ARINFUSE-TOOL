// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#include "arinfuse/camera_calibration/two_vanishing_points_calibration.h"

#include <cmath>
#include <iostream>
#include <string>

namespace dfki_av {
namespace arinfuse {

void TwoVanishingPointsCalibration::AddVanishingPoint(
    const cv::Point2i& vanishing_point) {
  std::cout << "vanishing_point(x: " << vanishing_point.x
            << ", y: " << vanishing_point.y << ")" << std::endl;
  points_.push_back(vanishing_point);
}

void TwoVanishingPointsCalibration::Reset() {
  points_.clear();
}

double TwoVanishingPointsCalibration::Calibrate(std::string* error) const {
  if (points_.size() < 2) {
    *error = "Not enough vanishing points";
    return 0;
  }
  if (points_.size() > 2) {
    *error = "To many vanishing points";
    return 0;
  }

  // If we have exactly two (orthogonal) vanishing points, f can be computed by
  //       0 = (x1 * x2) + (y1 * y2) + (f * f)

  cv::Point2i p1 = points_[0];
  cv::Point2i p2 = points_[1];

  double x = ((double)p1.x) * ((double)p2.x);
  double y = ((double)p1.y) * ((double)p2.y);

  double f_square = -(x + y);
  if (f_square < 0) {
    *error = "f^2 < 0, maybe the valishing points are not ortogonal?";
    return 0;
  }

  return std::sqrt(f_square);
}

}  // namespace arinfuse
}  // namespace dfki_av
