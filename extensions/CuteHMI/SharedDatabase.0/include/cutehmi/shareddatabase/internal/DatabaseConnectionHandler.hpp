#ifndef H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_0_INCLUDE_CUTEHMI_SHAREDDATABASE_INTERNAL_DATABASECONNECTIONHANDLER_HPP
#define H_EXTENSIONS_CUTEHMI_SHAREDDATABASE_0_INCLUDE_CUTEHMI_SHAREDDATABASE_INTERNAL_DATABASECONNECTIONHANDLER_HPP

#include "common.hpp"
#include "DatabaseConfig.hpp"

#include <cutehmi/InplaceError.hpp>

#include <QObject>
#include <QBasicTimer>
#include <QSqlDatabase>


namespace cutehmi {
namespace shareddatabase {
namespace internal {

class CUTEHMI_SHAREDDATABASE_PRIVATE DatabaseConnectionHandler:
	public QObject
{
		Q_OBJECT

		typedef QObject Parent;

	public:
		static constexpr int INITIAL_MONITOR_INTERVAL = 1000;

		static constexpr int INITIAL_MAINTENANCE_INTERVAL = 1000 * 60 * 60 * 12;

		DatabaseConnectionHandler(DatabaseConfig config, QObject * parent = nullptr);

	public slots:
		void connect();

		void disconnect();

	signals:
		void connected(QString connectionName);

		void disconnected(QString connectionName);

		void errored(cutehmi::InplaceError error);

	protected:
		void timerEvent(QTimerEvent * event) override;

	private slots:
		void printError(cutehmi::InplaceError error);

	private:
		struct Members
		{
			int monitorInterval;
			int maintenanceCount;
			DatabaseConfig config;
			QBasicTimer monitorTimer;
			QSqlDatabase db;
			QString connectionName;

			Members(DatabaseConfig p_config):
				monitorInterval(INITIAL_MONITOR_INTERVAL),
				maintenanceCount(0),
				config(p_config)
			{
			}
		};

		MPtr<Members> m;
};

}
}
}

#endif
