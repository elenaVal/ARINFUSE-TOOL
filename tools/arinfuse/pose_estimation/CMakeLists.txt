## Copyright 2020 DFKI GmbH - All Rights Reserved.
##
## This document is the property of DFKI GmbH.
## It is considered confidential and proprietary.
##
## This document may not be reproduced or transmitted in any form,
## in whole or in part, without the express written permission of
## Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

cmake_minimum_required(VERSION 3.4)

add_executable(pose_estimation
  main.cc
  pose_estimation.cc
  pose_estimation.h
  pose_estimation_window.cc
  pose_estimation_window.h
  # PnpSolver.cc
  # PnpSolver.h
)
target_link_libraries(pose_estimation
  opencv_calib3d
  opencv_core
  opencv_highgui
  opencv_imgproc
  Eigen3::Eigen

  camera_calibration_lib
  opencv_image_viewer
)
set_target_properties(pose_estimation
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON

    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
