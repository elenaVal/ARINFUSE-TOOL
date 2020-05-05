// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#include "arinfuse/camera_calibration/camera_calibration.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include "Eigen/Eigen"

namespace dfki_av {
namespace arinfuse {

// Reads a camera calibration from |path|.
Eigen::Matrix3d ReadCameraCalibration(const std::string& path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "Error opening camera calibration '" << path << "' for reading"
              << std::endl;
    std::terminate();
  }

  Eigen::Matrix3d calibration;

  float a;
  float b;
  float c;
  for (int row = 0; (file >> a >> b >> c); row++) {
    calibration(row, 0) = a;
    calibration(row, 1) = b;
    calibration(row, 2) = c;
  }

  file.close();
  return calibration;
}

// Writes a camera calibration to |path|.
void WriteCameraCalibration(
    const std::string& path, const Eigen::Matrix3d& calibration) {
  std::ofstream file(path);
  if (!file.is_open()) {
    std::cerr << "Error opening camera calibration '" << path << "' for writing"
              << std::endl;
    std::terminate();
  }

  for (int row = 0; row < 3; row++) {
    file << calibration(row, 0) << ' ' << calibration(row, 1) << ' '
         << calibration(row, 2) << std::endl;
  }
  file.close();
}

}  // namespace arinfuse
}  // namespace dfki_av
