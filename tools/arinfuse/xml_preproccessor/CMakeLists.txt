## Copyright 2020 DFKI GmbH - All Rights Reserved.
##
## This document is the property of DFKI GmbH.
## It is considered confidential and proprietary.
##
## This document may not be reproduced or transmitted in any form,
## in whole or in part, without the express written permission of
## Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

cmake_minimum_required(VERSION 3.4)

add_executable(xml_preproccessor
  main.cc
)
target_link_libraries(xml_preproccessor
  tinyxml
)
set_target_properties(xml_preproccessor
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON

    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
