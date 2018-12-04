#ifndef H_MODULES_CUTEHMI__STUPID__1_INCLUDE_CUTEHMI_STUPID_CLIENT_HPP
#define H_MODULES_CUTEHMI__STUPID__1_INCLUDE_CUTEHMI_STUPID_CLIENT_HPP

#include "internal/common.hpp"
#include "internal/DatabaseConnectionData.hpp"
#include "internal/DatabaseThread.hpp"
#include "internal/AsyncConnector.hpp"
#include "DS18B20.hpp"
#include "DS18B20History.hpp"

#include <cutehmi/ErrorInfo.hpp>

#include <QObject>
#include <QSqlError>

namespace cutehmi {
namespace stupid {

/**
 * STUPiD client.
 */
class CUTEHMI_STUPID_API Client:
	public QObject
{
	Q_OBJECT

	public:
		// Alternatively ds18b20 could be QQmlPropertyMap *, but QQmlPropertyMap can be modified from QML.
		// Const variant is not recognized, so QQmlPropertyMap would need to be extended to provide read-only access.
		Q_PROPERTY(const QVariantMap & ds18b20 READ ds18b20 NOTIFY ds18b20Changed)

		Q_PROPERTY(const QVariantMap & ds18b20History READ ds18b20History NOTIFY ds18b20HistoryChanged)

		typedef QList<QString> DS18B20IdsContainer;

		explicit Client(QObject * parent = nullptr);

		~Client() override;

		const QVariantMap & ds18b20() const;

		const QVariantMap & ds18b20History() const;

		DS18B20IdsContainer ds18b20Ids() const;

		/**
		 * Check if client is connected.
		 * @return @p true when client is connected. @p false otherwise.
		 *
		 * @note Because connection is established in asynchronous way, client
		 * can be in a sloppy state before it gets connected, thus this function
		 * and disconnected() may both return @p false at the same time.
		 */
		bool isConnected() const;

		/**
		 * Check if client is disconnected.
		 * @return @p true when client is disconnected. @p false otherwise.
		 */
		bool isDisconnected() const;

		void moveDatabaseConnectionData(std::unique_ptr<stupid::DatabaseConnectionData> dbData);

		void checkDatabaseConnectionStatus();

	public slots:
		/**
		 * Connect client to the STUPiD database.
		 */
		void connect();

		/**
		 * Disconnect client from the STUPiD database.
		 */
		void disconnect();

		/**
		 * Read all devices data.
		 *
		 * @param run indicates whether to interrupt read. Function interrupts reading and returns, if @p 0 is being set. If @p 1 is set
		 * function will return only after reading all values of coils and registers.
		 */
		void readAll(const QAtomicInt & run = 1);

	signals:
		void error(cutehmi::ErrorInfo errInfo);

		void connected();

		void disconnected();

		void ds18b20Changed();

		void ds18b20HistoryChanged();

	protected:
		// If there's no update for more than EXPIRE_MIN_INTERVAL + m_daemonSleep * EXPIRE_DAEMON_CYCLES, data should be marked as stalled.
		static constexpr int EXPIRE_DAEMON_CYCLES = 1;
		static constexpr int EXPIRE_MIN_INTERVAL = 30000;

		void asyncConnect(QObject * connector);

		void processSQLErrors();

		void clearDevices();

	private:
		typedef QVector<QSqlError> SQLErrorsContainer;

		struct Members
		{
			unsigned long daemonSleep = 0;
			bool connected = false;
			internal::AsyncConnector * asyncConnector = nullptr;
			internal::DatabaseThread dbThread;
			SQLErrorsContainer sqlErrors;
			QVariantMap ds18b20;
			QVariantMap ds18b20History;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
