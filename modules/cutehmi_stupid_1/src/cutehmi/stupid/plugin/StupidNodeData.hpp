#ifndef H_MODULES_CUTEHMI__STUPID__1_SRC_CUTEHMI_STUPID_PLUGIN_STUPIDNODEDATA_HPP
#define H_MODULES_CUTEHMI__STUPID__1_SRC_CUTEHMI_STUPID_PLUGIN_STUPIDNODEDATA_HPP

#include "../../../../include/cutehmi/stupid/Client.hpp"
#include "../../../../include/cutehmi/stupid/Service.hpp"

#include <cutehmi/DataBlock.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace stupid {
namespace plugin {

class StupidNodeData:
	public DataBlock
{
	public:
		StupidNodeData(std::unique_ptr<Client> client, std::unique_ptr<Service> service);

		~StupidNodeData() override = default;

		Client * client() const;

		Service * service() const;

	private:
		std::unique_ptr<Client> m_client;
		std::unique_ptr<Service> m_service;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
