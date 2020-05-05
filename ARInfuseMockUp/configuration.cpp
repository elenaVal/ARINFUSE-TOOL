#include "configuration.h"

namespace arinfuse {

// Inputs.
const std::string Configuration::kCameraPositionOffsetFile = "camera_mins.txt";
const std::string Configuration::kInputImageFile = "input.jpg";
const std::string Configuration::kRawXmlFile = "utilities.xml";
const std::string Configuration::kWorldPointsFile = "xyz.txt";

// Outputs.
const std::string Configuration::kAugmentedImageFile = "augmented_image.jpg";

// Intermediate artifacts.
const std::string Configuration::kCameraCalibrationFile = "params_ar.txt";
const std::string Configuration::kCameraPoseFile = "pose_ar.txt";
const std::string Configuration::kDepthPassFile = "depth_pass.pam";
const std::string Configuration::kIdPassFile = "id_pass.jpg";
const std::string Configuration::kPreprocessedXmlFile = "preprocessed.xml";
const std::string Configuration::kUnityOutputFile = "unity_putput.txt";

}  // namespace arinfuse
