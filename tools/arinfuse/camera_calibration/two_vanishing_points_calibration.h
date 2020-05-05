// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#ifndef ARINFUSE_CAMERA_CALIBRATION_TWO_VANISHING_POINTS_CALIBRATION_H_
#define ARINFUSE_CAMERA_CALIBRATION_TWO_VANISHING_POINTS_CALIBRATION_H_

#include <string>
#include <vector>

#include "arinfuse/camera_calibration/vanishing_points_calibration.h"
#include "opencv2/core.hpp"

namespace dfki_av {
namespace arinfuse {

class TwoVanishingPointsCalibration : public VanishingPointsCalibration {
 private:
  // VanishingPointsCalibration overrides.
  void AddVanishingPoint(const cv::Point2i& vanishing_point) override;
  void Reset() override;
  double Calibrate(std::string* error) const override;

  std::vector<cv::Point2i> points_;
};

}  // namespace arinfuse
}  // namespace dfki_av

#endif  // ARINFUSE_CAMERA_CALIBRATION_TWO_VANISHING_POINTS_CALIBRATION_H_
