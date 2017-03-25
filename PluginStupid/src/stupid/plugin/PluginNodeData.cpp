#include "PluginNodeData.hpp"

namespace cutehmi {
namespace stupid {
namespace plugin {

PluginNodeData::PluginNodeData(base::IXMLBackendPlugin * implementation):
	m_xmlBackendPlugin(new base::XMLBackendPlugin(implementation))
{
}

base::XMLBackendPlugin * PluginNodeData::xmlBackendPlugin() const
{
	return m_xmlBackendPlugin.get();
}

}
}
}
