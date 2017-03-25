#ifndef CUTEHMI_LIBSTUPID_INCLUDE_STUPID_SERVICE_HPP
#define CUTEHMI_LIBSTUPID_INCLUDE_STUPID_SERVICE_HPP


#include "internal/common.hpp"
#include "CommunicationThread.hpp"

#include <services/Service.hpp>

#include <memory>

namespace cutehmi {
namespace stupid {

class Client;

class CUTEHMI_STUPID_API Service:
	public services::Service
{
	public:
		Service(const QString & name, Client * client, QObject * parent = 0);

		~Service() override;

		unsigned long sleep() const;

		void setSleep(unsigned long sleep);

	protected:
		state_t customStart() override;

		state_t customStop() override;

	private:
		std::unique_ptr<CommunicationThread> m_thread;
		Client * m_client;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
