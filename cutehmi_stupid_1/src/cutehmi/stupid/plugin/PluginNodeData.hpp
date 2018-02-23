#ifndef CUTEHMI_CUTEHMI__STUPID__1_SRC_STUPID_PLUGIN_PLUGINNODEDATA_HPP
#define CUTEHMI_CUTEHMI__STUPID__1_SRC_STUPID_PLUGIN_PLUGINNODEDATA_HPP

#include <cutehmi/DataBlock.hpp>
#include <cutehmi/XMLBackendPlugin.hpp>

namespace cutehmi {
namespace stupid {
namespace plugin {

class PluginNodeData:
	public DataBlock
{
	public:
		PluginNodeData(IXMLBackendPlugin * implementation);

		XMLBackendPlugin * xmlBackendPlugin() const;

	private:
		std::unique_ptr<XMLBackendPlugin> m_xmlBackendPlugin;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
