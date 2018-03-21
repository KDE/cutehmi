#include "ModbusNodeData.hpp"

namespace cutehmi {
namespace modbus {
namespace plugin {

ModbusNodeData::ModbusNodeData(std::unique_ptr<Client> client, std::unique_ptr<Service> service):
	m_client(std::move(client)),
	m_service(std::move(service))
{
}

Client * ModbusNodeData::client() const
{
	return m_client.get();
}

Service * ModbusNodeData::service() const
{
	return m_service.get();
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
