// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#ifndef ARINFUSE_CAMERA_CALIBRATION_VANISHING_POINTS_CALIBRATION_H_
#define ARINFUSE_CAMERA_CALIBRATION_VANISHING_POINTS_CALIBRATION_H_

#include <string>

#include "opencv2/core.hpp"

namespace dfki_av {
namespace arinfuse {

// Pure-virtual base class for all calibration algorithms that operate on
// vanishing points.
class VanishingPointsCalibration {
 public:
  // Adds a vanishing point.
  virtual void AddVanishingPoint(const cv::Point2i& vanishing_point) = 0;

  virtual void Reset() = 0;

  virtual double Calibrate(std::string* error) const = 0;
};

}  // namespace arinfuse
}  // namespace dfki_av

#endif  // ARINFUSE_CAMERA_CALIBRATION_VANISHING_POINTS_CALIBRATION_H_
