## Copyright 2020 DFKI GmbH - All Rights Reserved.
##
## This document is the property of DFKI GmbH.
## It is considered confidential and proprietary.
##
## This document may not be reproduced or transmitted in any form,
## in whole or in part, without the express written permission of
## Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

cmake_minimum_required(VERSION 3.4)

add_library(camera_calibration_lib
  camera_calibration.cc
  camera_calibration.h
)
target_link_libraries(camera_calibration_lib
  opencv_core
  Eigen3::Eigen
)
set_target_properties(camera_calibration_lib
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON

    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

add_executable(camera_calibration
  calibration_window.cc
  calibration_window.h
  main.cc
  two_vanishing_points_calibration.cc
  two_vanishing_points_calibration.h
  vanishing_points_calibration.h
)
target_link_libraries(camera_calibration
  opencv_core
  opencv_imgproc
  opencv_highgui

  camera_calibration_lib
  opencv_image_viewer
)
set_target_properties(camera_calibration
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON

    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
