#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_NODEDATAOBJECT_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_NODEDATAOBJECT_HPP

#include "Client.hpp"
#include "Service.hpp"

#include <QObject>

#include <memory>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API NodeDataObject:
	public QObject
{
	Q_OBJECT

	public:
		NodeDataObject(std::unique_ptr<Client> client, std::unique_ptr<Service> service, QObject * parent = nullptr);

		~NodeDataObject() override = default;

		Client * client() const;

		Service * service() const;

	private:
		std::unique_ptr<Client> m_client;
		std::unique_ptr<Service> m_service;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
