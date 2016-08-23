#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_SERVICE_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_SERVICE_HPP

#include "../platform.hpp"
#include "CommunicationThread.hpp"

#include <base/IService.hpp>

#include <memory>

namespace cutehmi {
namespace modbus {

class Client;

class CUTEHMI_MODBUS_API Service:
	public base::IService
{
	public:
		Service(Client * client);

		virtual ~Service();

		unsigned long sleep() const;

		void setSleep(unsigned long sleep);

		void start() override;

		void stop() override;

	private:
		std::unique_ptr<CommunicationThread> m_thread;
		Client * m_client;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
