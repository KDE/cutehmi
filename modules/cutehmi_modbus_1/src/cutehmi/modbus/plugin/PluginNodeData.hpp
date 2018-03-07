#ifndef H_MODULES_CUTEHMI__MODBUS__1_SRC_CUTEHMI_MODBUS_PLUGIN_PLUGINNODEDATA_HPP
#define H_MODULES_CUTEHMI__MODBUS__1_SRC_CUTEHMI_MODBUS_PLUGIN_PLUGINNODEDATA_HPP

#include <cutehmi/xml/BackendPlugin.hpp>

#include <cutehmi/DataBlock.hpp>

namespace cutehmi {
namespace modbus {
namespace plugin {

class PluginNodeData:
	public DataBlock
{
	public:
		PluginNodeData(xml::IBackendPlugin * implementation);

		xml::BackendPlugin * xmlBackendPlugin() const;

	private:
		std::unique_ptr<xml::BackendPlugin> m_xmlBackendPlugin;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
