// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#ifndef OPENCV_UTILS_OPENCV_IMAGE_VIEWER_H_
#define OPENCV_UTILS_OPENCV_IMAGE_VIEWER_H_

#include <string>

#include "opencv2/core.hpp"

namespace dfki_av {
namespace tools {

// Utility class for using the OpenCV highgui module with an OO API.
class OpenCVImageViewer {
 public:
  OpenCVImageViewer(const std::string& window_name);
  virtual ~OpenCVImageViewer();

  // Shows an image.
  void DrawImage(const cv::Mat& image) const;

 private:
  // Called whenever the position of the mouse (in the window) changes.
  virtual void MouseCallback(int event, int x, int y, int flags);

  // Internal helper to use with the OpenCV API.
  static void MouseCallback(int event, int x, int y, int flags, void* data);

  std::string name_;
};

}  // namespace tools
}  // namespace dfki_av

#endif  // OPENCV_UTILS_OPENCV_IMAGE_VIEWER_H_
