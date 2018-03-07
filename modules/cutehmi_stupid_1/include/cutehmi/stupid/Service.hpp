#ifndef H_MODULES_CUTEHMI__STUPID__1_INCLUDE_CUTEHMI_STUPID_SERVICE_HPP
#define H_MODULES_CUTEHMI__STUPID__1_INCLUDE_CUTEHMI_STUPID_SERVICE_HPP

#include "internal/common.hpp"
#include "internal/CommunicationThread.hpp"

#include <cutehmi/ErrorInfo.hpp>

#include <cutehmi/services/Service.hpp>

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

	private slots:
		void onClientConnected();

		void onClientDisconnected();

		void handleError(cutehmi::ErrorInfo errorInfo);

	private:
		struct Members
		{
			std::unique_ptr<internal::CommunicationThread> thread;
			Client * client;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
