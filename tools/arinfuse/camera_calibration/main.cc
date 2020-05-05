// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#include <fstream>
#include <iostream>
#include <string>

#include "Eigen/Eigen"
#include "arinfuse/camera_calibration/calibration_window.h"
#include "arinfuse/camera_calibration/camera_calibration.h"
#include "arinfuse/camera_calibration/two_vanishing_points_calibration.h"
#include "arinfuse/camera_calibration/vanishing_points_calibration.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

namespace dfki_av {
namespace arinfuse {
namespace {

int RunCalibration(
    const cv::Mat& image,
    VanishingPointsCalibration* vanishing_points_calibration,
    const std::string& camera_calibration_path) {
  std::string error;
  double f = vanishing_points_calibration->Calibrate(&error);
  if ("" != error) {
    std::cerr << "Error during calibration: " << error << std::endl;
    return 4;
  }

  int cx = image.size().width / 2;
  int cy = image.size().height / 2;

  double fx = f / image.size().width;
  double fy = f / image.size().height;

  Eigen::Matrix3d camera_calibration = Eigen::Matrix3d::Identity();
  camera_calibration(0, 0) = image.size().width / fx;
  camera_calibration(1, 1) = image.size().height / fy;
  camera_calibration(0, 2) = cx;
  camera_calibration(1, 2) = cy;

  WriteCameraCalibration(camera_calibration_path, camera_calibration);

  return 0;
}

int CameraCalibrationMain(
    const std::string& image_path, const std::string& camera_calibration_path) {
  cv::Mat image = cv::imread(image_path);
  if (!image.size().width || !image.size().height) {
    std::cerr << "Error opening image '" << image_path << "'" << std::endl;
    return 2;
  }

  TwoVanishingPointsCalibration two_vanishing_points_calibration;
  CalibrationWindow window(&two_vanishing_points_calibration, image);

  while (true) {
    switch ((char)cv::waitKey(0)) {
      case 'q':
        std::cerr << "Quitting without calibrating" << std::endl;
        return 3;

      case 'r':
        std::cerr << "Resetting calibration" << std::endl;
        window.Reset();
        break;

      case 'c':
        return RunCalibration(
            image, &two_vanishing_points_calibration, camera_calibration_path);

      default:
        break;
    }
  }
}

}  // namespace
}  // namespace arinfuse
}  // namespace dfki_av

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: camera_calibration <path/to/image> <path/to/output>"
              << std::endl;
    return 1;
  }

  return dfki_av::arinfuse::CameraCalibrationMain(argv[1], argv[2]);
}
