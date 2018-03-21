#include "../../../include/cutehmi/internal/PluginNodeData.hpp"
#include "../../../include/cutehmi/Plugin.hpp"
#include "../../../include/cutehmi/IProjectPlugin.hpp"

namespace cutehmi {
namespace internal {

PluginNodeData::PluginNodeData(Plugin * plugin, int reqMinor):
	m(new Members{plugin, reqMinor})
{
}

Plugin * PluginNodeData::plugin() const
{
	return m->plugin;
}

int PluginNodeData::reqMinor() const
{
	return m->reqMinor;
}

IProjectPlugin * PluginNodeData::pluginInstance() const
{
	CUTEHMI_ASSERT(qobject_cast<IProjectPlugin *>(m->plugin->instance()), "plugin instance does not implement IProjectPlugin interface");

	return qobject_cast<IProjectPlugin *>(m->plugin->instance());
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
