#ifndef H_MODULES_CUTEHMI__STUPID__1_INCLUDE_CUTEHMI_STUPID_INTERNAL_ASYNCCONNECTOR_HPP
#define H_MODULES_CUTEHMI__STUPID__1_INCLUDE_CUTEHMI_STUPID_INTERNAL_ASYNCCONNECTOR_HPP

#include "common.hpp"
#include "Worker.hpp"
#include "DatabaseThread.hpp"

#include <QStringList>

namespace cutehmi {
namespace stupid {
namespace internal {

class AsyncConnector:
	public QObject
{
	Q_OBJECT

	public:
		enum Status {
			INIT,
			ENUMERATE_DEVICES,
			LOAD_DAEMON_SLEEP,
			FINALIZE,
			CONNECTED
		};

		AsyncConnector(DatabaseThread * dbThread, QObject * parent = 0);

		const QStringList & w1Ids() const;

		unsigned long daemonSleep() const;

		Status status() const;

	public slots:
		void connect();

	signals:
		void connected(QObject * connector);

	private:
		DatabaseThread * m_dbThread;
		Worker m_dbWorker;
		unsigned long m_daemonSleep;
		QStringList m_w1Ids;
		Status m_status;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
