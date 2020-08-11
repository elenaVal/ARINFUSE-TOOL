## Copyright 2020 DFKI GmbH - All Rights Reserved.
##
## This document is the property of DFKI GmbH.
## It is considered confidential and proprietary.
##
## This document may not be reproduced or transmitted in any form,
## in whole or in part, without the express written permission of
## Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

cmake_minimum_required(VERSION 3.4)

# TODO(yannic): Suppress warnings.

add_library(tinyxml
  STATIC
    include/tinystr.h
    include/tinyxml.h
    src/tinystr.cpp
    src/tinyxml.cpp
    src/tinyxmlerror.cpp
    src/tinyxmlparser.cpp
)
target_include_directories(tinyxml
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
set_target_properties(tinyxml
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON

    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
