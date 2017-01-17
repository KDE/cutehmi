#ifndef CUTEHMI_LIBSTUPID_SRC_STUPID_CLIENT_HPP
#define CUTEHMI_LIBSTUPID_SRC_STUPID_CLIENT_HPP

#include "../platform.hpp"
#include "DS18B20.hpp"
#include "DS18B20History.hpp"
#include "DatabaseConnectionData.hpp"
#include "DatabaseThread.hpp"

#include <base/ErrorInfo.hpp>

#include <QObject>

#include <memory>

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

//		struct CUTEHMI_STUPID_API Error:
//			public base::Error
//		{
//			enum : int {
//			};

//			using base::Error::Error;

//			QString str() const;
//		};

		typedef QList<QString> DS18B20IdsContainer;

		explicit Client(QObject * parent = 0);

		~Client() override;

//		const QQmlListProperty<DS18B20> & ds18b20() const;

//		QQmlPropertyMap * ds18b20();

		const QVariantMap & ds18b20() const;

		const QVariantMap & ds18b20History() const;

//		/**
//		 * Read input register value and update associated InputRegister object.
//		 * @param addr register address.
//		 *
//		 * @note appropriate InputRegister object must be referenced using @a ir list before using this function.
//		 */
//		void readDS18B20(const QString & id);

		DS18B20IdsContainer ds18b20Ids() const;

		void moveDatabaseConnectionData(std::unique_ptr<stupid::DatabaseConnectionData> dbData);

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
		void error(cutehmi::base::ErrorInfo errInfo);

		void connected();

		void disconnected();

		void ds18b20Changed();

		void ds18b20HistoryChanged();

	protected:
		// If there's no update for more than EXPIRE_MIN_INTERVAL + m_daemonSleep * EXPIRE_DAEMON_CYCLES, data should be marked as stalled.
		static constexpr int EXPIRE_DAEMON_CYCLES = 1;
		static constexpr int EXPIRE_MIN_INTERVAL = 30000;

		void enumerateDevices();

		void loadDaemonSleep();

	private:
		void clearDevices();

		DatabaseThread m_dbThread;
		unsigned long m_daemonSleep;
		QVariantMap m_ds18b20;
		QVariantMap m_ds18b20History;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
