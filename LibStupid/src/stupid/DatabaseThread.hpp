#ifndef DATABASETHREAD_H
#define DATABASETHREAD_H

#include "../platform.hpp"
#include "Worker.hpp"
#include "DatabaseConnectionData.hpp"

#include <base/ErrorInfo.hpp>

#include <QThread>

#include <memory>

namespace cutehmi {
namespace stupid {

class CUTEHMI_STUPID_API DatabaseThread:
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
		std::unique_ptr<DatabaseConnectionData> m_dbData;
		QMutex m_runLock;
};

}
}

#endif // DATABASETHREAD_H
