#ifndef H_MODULES_CUTEHMI__SERVICES__1_SRC_CUTEHMI_SERVICES_PLUGIN_PLUGINNODEDATA_HPP
#define H_MODULES_CUTEHMI__SERVICES__1_SRC_CUTEHMI_SERVICES_PLUGIN_PLUGINNODEDATA_HPP

#include "../../../../include/cutehmi/services/ServiceRegistry.hpp"

#include <cutehmi/DataBlock.hpp>

namespace cutehmi {
namespace services {
namespace plugin {

class PluginNodeData:
	public DataBlock
{
	public:
		PluginNodeData();

		ServiceRegistry * serviceRegistry() const;

	private:
		std::unique_ptr<ServiceRegistry> m_serviceRegistry;
};

}
}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
