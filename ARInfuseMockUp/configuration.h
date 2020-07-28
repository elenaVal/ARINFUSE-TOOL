#ifndef ARINFUSE_CONFIGURATION_H_
#define ARINFUSE_CONFIGURATION_H_

#include <string>

namespace arinfuse {

// Provides access to the current configuration.
class Configuration {
 public:
   // Inputs.
   static const std::string kCameraPositionOffsetFile;
   static const std::string kInputImageFile;
   static const std::string kRawXmlFile;
   static const std::string kWorldPointsFile;

   // Outputs.
   static const std::string kAugmentedImageFile;

   // Intermediate artifacts.
   static const std::string kCameraCalibrationFile;
   static const std::string kCameraPoseFile;
   static const std::string kDepthPassFile;
   static const std::string kIdPassFile;
   static const std::string kPreprocessedXmlFile;
   static const std::string kUnityOutputFile;
   static const std::string KStreetLevel;

   virtual std::string GetDataFilePath(const std::string &file) const = 0;
   virtual std::string GetToolPath(const std::string &tool) const = 0;
};

}  // namespace arinfuse

#endif // ARINFUSE_CONFIGURATION_H_
