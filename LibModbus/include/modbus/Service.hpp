#ifndef CUTEHMI_LIBMODBUS_INCLUDE_MODBUS_SERVICE_HPP
#define CUTEHMI_LIBMODBUS_INCLUDE_MODBUS_SERVICE_HPP

#include "internal/common.hpp"
#include "internal/CommunicationThread.hpp"

#include <services/Service.hpp>

#include <memory>

namespace cutehmi {
namespace modbus {

class Client;

class CUTEHMI_MODBUS_API Service:
	public services::Service
{
	public:
		Service(const QString & name, Client * client, QObject * parent = 0);

		virtual ~Service();

		unsigned long sleep() const;

		void setSleep(unsigned long sleep);

	protected:
		state_t customStart() override;

		state_t customStop() override;

	private:
		struct Members
		{
			std::unique_ptr<internal::CommunicationThread> thread;
			Client * client;

			Members(Client * p_client):
				thread(new internal::CommunicationThread(p_client)),
				client(p_client)
			{
			}
		};

		utils::MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
