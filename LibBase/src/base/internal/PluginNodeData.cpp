#include "../../../include/base/internal/PluginNodeData.hpp"

namespace cutehmi {
namespace base {
namespace internal {

PluginNodeData::PluginNodeData(Plugin * plugin, const QString & minVersion):
	m(new Members{plugin, minVersion})
{
}

Plugin * PluginNodeData::plugin() const
{
	return m->plugin;
}

QString PluginNodeData::minVersion() const
{
	return m->minVersion;
}

IPlugin * PluginNodeData::pluginInstance() const
{
	CUTEHMI_BASE_ASSERT(qobject_cast<IPlugin *>(m->plugin->instance()), "plugin instance does not implement IPlugin interface");

	return qobject_cast<IPlugin *>(m->plugin->instance());
}

}
}
}
