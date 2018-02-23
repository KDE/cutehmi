#include "PluginNodeData.hpp"

namespace cutehmi {
namespace stupid {
namespace plugin {

PluginNodeData::PluginNodeData(IXMLBackendPlugin * implementation):
	m_xmlBackendPlugin(new XMLBackendPlugin(implementation))
{
}

XMLBackendPlugin * PluginNodeData::xmlBackendPlugin() const
{
	return m_xmlBackendPlugin.get();
}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
