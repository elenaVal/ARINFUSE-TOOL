#include "settings_view.h"

#include <string>

namespace arinfuse {

SettingsView::SettingsView(const std::string& default_tool_path,
                           const std::string& default_data_path)
    : tool_path_(default_tool_path), data_path_(default_data_path) {}

void SettingsView::UpdateDataPath(const std::string& data_path) {
  data_path_ = data_path;
}

void SettingsView::UpdateToolPath(const std::string& tool_path) {
  tool_path_ = tool_path;
}

std::string SettingsView::GetDataFilePath(const std::string& file) const {
  return data_path_ + "/" + file;
}

std::string SettingsView::GetToolPath(const std::string& tool) const {
  return tool_path_ + "/" + tool;
}

}  // namespace arinfuse
