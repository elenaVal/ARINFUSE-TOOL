// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Eigen/Eigen"
#include "arinfuse/camera_calibration/camera_calibration.h"
#include "arinfuse/pose_estimation/pose_estimation.h"
#include "arinfuse/pose_estimation/pose_estimation_window.h"
#include "opencv2/core.hpp"
#include "opencv2/core/eigen.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

namespace dfki_av {
namespace arinfuse {
namespace {

cv::Mat ReadImage(const std::string& path) {
  cv::Mat image = cv::imread(path);
  if (!image.size().width || !image.size().height) {
    std::cerr << "Error opening image '" << path << "'" << std::endl;
    std::terminate();
  }
  return image;
}

cv::Point3d ReadCameraMins(const std::string& path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "Error opening camera mins file '" << path << "'" << std::endl;
    std::terminate();
  }

  cv::Point3d camera_mins(0, 0, 0);
  file >> camera_mins.x >> camera_mins.y;
  return camera_mins;
}

std::vector<cv::Point3d> ReadWorldCoordinates(
    const std::string& path, const std::string& camera_mins_path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "Error opening world coordinates file '" << path << "'"
              << std::endl;
    std::terminate();
  }

  cv::Point3d camera_mins = ReadCameraMins(camera_mins_path);

  std::vector<cv::Point3d> points;

  double x;
  double y;
  double z;
  char c;
  while (file >> c >> x >> y >> z) {
    if (c != '#') {
      points.push_back(
          cv::Point3d(x - camera_mins.x, y - camera_mins.y, z - camera_mins.z));
    }
  }

  return points;
}

void WritePose(const std::string& path, const Eigen::Matrix4d& pose) {
  // The rotation matrix needs to be transposed for Unity renderer.
  Eigen::Matrix4d unity_pose = pose.transpose();

  std::ofstream file(path);
  if (!file.is_open()) {
    std::cerr << "Error opening pose '" << path << "' for writing" << std::endl;
    std::terminate();
  }

  for (int row = 0; row < 4; row++) {
    file << unity_pose(row, 0) << ' ' << unity_pose(row, 1) << ' '
         << unity_pose(row, 2) << ' ' << unity_pose(row, 3) << std::endl;
  }
  file.close();
}

int PoseEstimationMain(
    const std::string& image_path,
    const std::string& camera_calibration_path,
    const std::string& world_coordinates_path,
    const std::string& camera_mins_path,
    const std::string& pose_path) {
  cv::Mat image = ReadImage(image_path);

  std::vector<cv::Point3d> world_points =
      ReadWorldCoordinates(world_coordinates_path, camera_mins_path);
  Eigen::Matrix3d camera_calibration =
      ReadCameraCalibration(camera_calibration_path);
  PoseEstimation pose_estimation(world_points, camera_calibration);

  PoseEstimationWindow window(&pose_estimation, image);
  while (true) {
    switch ((char)cv::waitKey(0)) {
      case 'q':
        std::cerr << "Quitting without estimating pose" << std::endl;
        return 3;

      case 'r':
      reset:
        std::cerr << "Resetting pose esimation" << std::endl;
        window.Reset();
        break;

      case 'c': {
        Eigen::Matrix4d pose = pose_estimation.EstimatePose();
        window.ReprojectWorldPoints(world_points, camera_calibration, pose);
        while (true) {
          switch ((char)cv::waitKey(0)) {
            case 'q':
              std::cerr << "Quitting without saving pose" << std::endl;
              return 3;

            case 'r':
              goto reset;

            case 's':
              WritePose(pose_path, pose);
              return 0;

            default:
              break;
          }
        }

        // UNREACHED
        std::terminate();
      }

      default:
        break;
    }
  }
}

}  // namespace
}  // namespace arinfuse
}  // namespace dfki_av

int main(int argc, char* argv[]) {
  if (argc != 6) {
    std::cerr << "Usage: pose_estimation "
              << "<path/to/image> "
              << "<path/to/camera_calibration> "
              << "<path/to/world_points> "
              << "<path/to/camera_mins> "
              << "<path/to/output>" << std::endl;
    return 1;
  }

  return dfki_av::arinfuse::PoseEstimationMain(
      argv[1], argv[2], argv[3], argv[4], argv[5]);
}
