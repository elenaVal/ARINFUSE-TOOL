// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#ifndef ARINFUSE_CAMERA_CALIBRATION_CAMERA_CALIBRATION_H_
#define ARINFUSE_CAMERA_CALIBRATION_CAMERA_CALIBRATION_H_

#include <string>

#include "Eigen/Eigen"

namespace dfki_av {
namespace arinfuse {

// Reads a camera calibration from |path|.
Eigen::Matrix3d ReadCameraCalibration(const std::string& path);

// Writes a camera calibration to |path|.
void WriteCameraCalibration(
    const std::string& path, const Eigen::Matrix3d& calibration);

}  // namespace arinfuse
}  // namespace dfki_av

#endif  // ARINFUSE_CAMERA_CALIBRATION_CAMERA_CALIBRATION_H_
