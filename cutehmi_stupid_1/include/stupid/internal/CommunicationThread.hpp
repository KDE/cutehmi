#ifndef CUTEHMI_CUTEHMI__STUPID__1__LIB_INCLUDE_STUPID_INTERNAL_COMMUNICATIONTHREAD_HPP
#define CUTEHMI_CUTEHMI__STUPID__1__LIB_INCLUDE_STUPID_INTERNAL_COMMUNICATIONTHREAD_HPP

#include "common.hpp"

#include <QThread>
#include <QAtomicInt>

namespace cutehmi {
namespace stupid {

class Client;

namespace internal {

class CommunicationThread:
	public QThread
{
	Q_OBJECT
	typedef QThread Parent;

	public:
		explicit CommunicationThread(Client * client);

	public:
		unsigned long sleep() const;

		void setSleep(unsigned long sleep);

		void run() override;

	public slots:
		void start();

		void stop();

	private:
		struct Members
		{
			QAtomicInt run;
			unsigned long sleep;
			Client * client;
		};

		utils::MPtr<Members> m;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
