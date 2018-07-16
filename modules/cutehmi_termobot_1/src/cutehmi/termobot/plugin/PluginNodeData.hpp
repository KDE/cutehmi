#ifndef PLUGINNODEDATA_HPP
#define PLUGINNODEDATA_HPP

#include <cutehmi/xml/BackendPlugin.hpp>

#include <cutehmi/DataBlock.hpp>

namespace cutehmi {
namespace termobot {
namespace plugin {

class PluginNodeData : public DataBlock {
public:
  PluginNodeData(xml::IBackendPlugin *implementation);

  xml::BackendPlugin *xmlBackendPlugin() const;

private:
  std::unique_ptr<xml::BackendPlugin> x_xmlBackendPlugin;
};

} // namespace plugin
} // namespace termobot
} // namespace cutehmi

#endif // PLUGINNODEDATA_HPP
