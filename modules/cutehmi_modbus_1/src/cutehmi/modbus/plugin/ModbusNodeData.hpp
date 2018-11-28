#ifndef H_MODULES_CUTEHMI_u_MODBUS_u_1_SRC_CUTEHMI_MODBUS_PLUGIN_MODBUSNODEDATA_HPP
#define H_MODULES_CUTEHMI_u_MODBUS_u_1_SRC_CUTEHMI_MODBUS_PLUGIN_MODBUSNODEDATA_HPP

#include "../../../../include/cutehmi/modbus/Client.hpp"
#include "../../../../include/cutehmi/modbus/Service.hpp"

#include <cutehmi/DataBlock.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace modbus {
namespace plugin {

class ModbusNodeData:
	public DataBlock
{
	public:
		ModbusNodeData(std::unique_ptr<Client> client, std::unique_ptr<Service> service);

		~ModbusNodeData() override = default;

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

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
