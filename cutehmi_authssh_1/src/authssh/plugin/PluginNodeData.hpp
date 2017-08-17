#ifndef CUTEHMI_CUTEHMI__AUTHSSH__1_SRC_AUTHSSH_PLUGIN_PLUGINNODEDATA_HPP
#define CUTEHMI_CUTEHMI__AUTHSSH__1_SRC_AUTHSSH_PLUGIN_PLUGINNODEDATA_HPP

#include <base/DataBlock.hpp>
#include <base/XMLBackendPlugin.hpp>

namespace cutehmi {
namespace authssh {
namespace plugin {

class PluginNodeData:
	public base::DataBlock
{
	public:
		PluginNodeData(base::IXMLBackendPlugin * implementation);

		base::XMLBackendPlugin * xmlBackendPlugin() const;

	private:
		std::unique_ptr<base::XMLBackendPlugin> m_xmlBackendPlugin;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
