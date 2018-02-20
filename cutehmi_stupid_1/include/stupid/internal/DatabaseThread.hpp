#ifndef CUTEHMI_CUTEHMI__STUPID__1__LIB_INCLUDE_STUPID_INTERNAL_DATABASETHREAD_HPP
#define CUTEHMI_CUTEHMI__STUPID__1__LIB_INCLUDE_STUPID_INTERNAL_DATABASETHREAD_HPP

#include "common.hpp"
#include "Worker.hpp"
#include "DatabaseConnectionData.hpp"

#include <cutehmi/ErrorInfo.hpp>

#include <QThread>

#include <memory>

namespace cutehmi {
namespace stupid {
namespace internal {

class DatabaseThread:
		public QThread
{
	Q_OBJECT

	public:
		struct CUTEHMI_STUPID_API Error:
			public base::Error
		{
			enum : int {
				NOT_CONFIGURED = base::Error::SUBCLASS_BEGIN,
				UNABLE_TO_CONNECT
			};

			using base::Error::Error;

			QString str() const;
		};

		DatabaseThread();

		void moveDatabaseConnectionData(std::unique_ptr<stupid::DatabaseConnectionData> dbData);

		stupid::DatabaseConnectionData * dbData() const;

	signals:
		void error(cutehmi::base::ErrorInfo errInfo);

		void connected();

		void disconnected();

	protected:
		void run() override;

	private:
		struct Members
		{
			std::unique_ptr<DatabaseConnectionData> dbData;
			QMutex runLock;
		};

		utils::MPtr<Members> m;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
