#ifndef ARINFUSE_SETTINGS_VIEW_H_
#define ARINFUSE_SETTINGS_VIEW_H_

#include <string>

#include "configuration.h"

namespace arinfuse {

// Encapsulates functions of the settings tab.
class SettingsView : public arinfuse::Configuration {
 public:
  SettingsView(
      const std::string& default_tool_path,
      const std::string& default_data_path);

  void UpdateDataPath(const std::string& data_path);
  void UpdateToolPath(const std::string& tool_path);

   // arinfuse::Configuration overrides.
   std::string GetDataFilePath(const std::string& file) const override;
   std::string GetToolPath(const std::string& tool) const override;

 private:
  std::string tool_path_;
  std::string data_path_;
};

}  // namespace arinfuse

#endif // ARINFUSE_SETTINGS_VIEW_H_
