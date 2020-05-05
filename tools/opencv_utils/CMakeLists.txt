## Copyright 2020 DFKI GmbH - All Rights Reserved.
##
## This document is the property of DFKI GmbH.
## It is considered confidential and proprietary.
##
## This document may not be reproduced or transmitted in any form,
## in whole or in part, without the express written permission of
## Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

cmake_minimum_required(VERSION 3.4)

add_library(opencv_image_viewer
  opencv_image_viewer.cc
  opencv_image_viewer.h
)
target_link_libraries(opencv_image_viewer
  opencv_core
  opencv_highgui
)
set_target_properties(opencv_image_viewer
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON

    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
