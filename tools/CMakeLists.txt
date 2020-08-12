## Copyright 2020 DFKI GmbH - All Rights Reserved.
##
## This document is the property of DFKI GmbH.
## It is considered confidential and proprietary.
##
## This document may not be reproduced or transmitted in any form,
## in whole or in part, without the express written permission of
## Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

cmake_minimum_required(VERSION 3.4)

project(arinfuse)

set(OpenCV_STATIC ON)
find_package(OpenCV 3.4.1 REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(
  BEFORE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_subdirectory(arinfuse)
add_subdirectory(opencv_utils)
add_subdirectory(third_party)
