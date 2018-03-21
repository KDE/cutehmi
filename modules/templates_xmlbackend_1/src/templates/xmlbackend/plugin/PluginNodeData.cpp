#include "PluginNodeData.hpp"

namespace templates {        // Edit! Replace 'templates' with custom vendor id.
namespace xmlbackend {    // Edit! Replace 'xmlbackend' with custom module id.
namespace plugin {

PluginNodeData::PluginNodeData(cutehmi::xml::IBackendPlugin * implementation):
	m_xmlBackendPlugin(new cutehmi::xml::BackendPlugin(implementation))
{
}

cutehmi::xml::BackendPlugin * PluginNodeData::xmlBackendPlugin() const
{
	return m_xmlBackendPlugin.get();
}

}
}
}

