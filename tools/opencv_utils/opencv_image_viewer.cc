// Copyright 2020 DFKI GmbH - All Rights Reserved.
//
// This document is the property of DFKI GmbH.
// It is considered confidential and proprietary.
//
// This document may not be reproduced or transmitted in any form,
// in whole or in part, without the express written permission of
// Deutsches Forschungszentrum für Künstliche Intelligenz GmbH.

#include "opencv_utils/opencv_image_viewer.h"

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

namespace dfki_av {
namespace tools {

OpenCVImageViewer::OpenCVImageViewer(const std::string& window_name)
    : name_(window_name) {
  cv::namedWindow(name_, cv::WINDOW_NORMAL | cv::WINDOW_KEEPRATIO);
#if defined(_WIN32)
  cv::setWindowProperty(name_, cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
#endif  // defined(_WIN32)
  cv::setMouseCallback(name_, &OpenCVImageViewer::MouseCallback, this);
}

OpenCVImageViewer::~OpenCVImageViewer() {
  cv::destroyWindow(name_);
}

void OpenCVImageViewer::DrawImage(const cv::Mat& image) const {
  cv::imshow(name_, image);
}

void OpenCVImageViewer::MouseCallback(int event, int x, int y, int flags) {
  // By default, this method doesn't do anything.
}

// static
void OpenCVImageViewer::MouseCallback(
    int event, int x, int y, int flags, void* data) {
  OpenCVImageViewer* obj = static_cast<OpenCVImageViewer*>(data);
  obj->MouseCallback(event, x, y, flags);
}

}  // namespace tools
}  // namespace dfki_av
