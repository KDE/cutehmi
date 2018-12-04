#ifndef H_MODULES_CUTEHMI__MODBUS__1_INCLUDE_CUTEHMI_MODBUS_SERVICE_HPP
#define H_MODULES_CUTEHMI__MODBUS__1_INCLUDE_CUTEHMI_MODBUS_SERVICE_HPP

#include "internal/common.hpp"
#include "internal/ServiceThread.hpp"

#include <cutehmi/ErrorInfo.hpp>
#include <cutehmi/services/Service.hpp>

#include <QStateMachine>

#include <memory>

namespace cutehmi {
namespace modbus {

class Client;

class CUTEHMI_MODBUS_API Service:
	public services::Service
{
	Q_OBJECT

	public:
		Service(const QString & name, Client * client, QObject * parent = nullptr);

		~Service() override;

		unsigned long sleep() const;

		void setSleep(unsigned long sleep);

	signals:
		void customStartRequested();

		void customStopRequested();

		void brokenTimeoutTriggered();

	protected:
		State customStart() override;

		State customStop() override;

	private slots:
		void startServiceThread();

		void stopServiceThread();

		void onStartedEntered();

		void onStoppedEntered();

		void onBrokenEntered();

		void onBrokenWaitEntered();

		void onBrokenWaitExited();

		void handleError(cutehmi::ErrorInfo errorInfo);

	private:
		static constexpr long MAX_BROKEN_SERVICE_WAIT = 600000; // [ms] = 10 minutes.
		static constexpr int INITIAL_BROKEN_SERVICE_WAIT = 5000; // [ms] = 5 seconds.

		struct Members
		{
			std::unique_ptr<internal::ServiceThread> thread;
			Client * client;
			QStateMachine sm;
			int brokenServiceWait;

			Members(Client * p_client):
				thread(new internal::ServiceThread(p_client)),
				client(p_client),
				brokenServiceWait(INITIAL_BROKEN_SERVICE_WAIT)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
