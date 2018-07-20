#include "PluginNodeData.hpp"

namespace cutehmi {
namespace termobot {
namespace plugin {

PluginNodeData::PluginNodeData(xml::IBackendPlugin *implementation)
    : m_xmlBackendPlugin(new xml::BackendPlugin(implementation)) {}

xml::BackendPlugin *PluginNodeData::xmlBackendPlugin() const {
  return m_xmlBackendPlugin.get();
}

} // namespace plugin
} // namespace termobot
} // namespace cutehmi
