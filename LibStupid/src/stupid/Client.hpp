#ifndef CUTEHMI_LIBSTUPID_SRC_STUPID_CLIENT_HPP
#define CUTEHMI_LIBSTUPID_SRC_STUPID_CLIENT_HPP

#include "../platform.hpp"
#include "DS18B20.hpp"

#include <base/ErrorInfo.hpp>

#include <QObject>
//#include <QQmlListProperty>
#include <QQmlPropertyMap>

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

	// Alternatively ds18b20 could be QQmlPropertyMap *, but QQmlPropertyMap can be modified from QML.
	// Const variant is not recognized, so QQmlPropertyMap would need to be extended to provide read-only access.
	Q_PROPERTY(const QVariantMap & ds18b20 READ ds18b20)

	public:
		struct CUTEHMI_STUPID_API Error:
			public base::Error
		{
			enum : int {
				UNABLE_TO_CONNECT = base::Error::SUBCLASS_BEGIN
			};

			using base::Error::Error;

			QString str() const;
		};

		typedef QList<QString> DS18B20IdsContainer;

		explicit Client(const QString & connectionName, QObject * parent = 0);

		~Client() override;

//		const QQmlListProperty<DS18B20> & ds18b20() const;

//		QQmlPropertyMap * ds18b20();

		const QVariantMap & ds18b20() const;

//		/**
//		 * Read input register value and update associated InputRegister object.
//		 * @param addr register address.
//		 *
//		 * @note appropriate InputRegister object must be referenced using @a ir list before using this function.
//		 */
//		void readDS18B20(const QString & id);

		DS18B20IdsContainer ds18b20Ids() const;

	public slots:
		void init();

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
		void error(base::ErrorInfo errInfo);

		void connected();

		void disconnected();

	protected:
		// If there's no update for more than EXPIRE_MIN_INTERVAL + m_daemonSleep * EXPIRE_DAEMON_CYCLES, data should be marked as stalled.
		static constexpr int EXPIRE_DAEMON_CYCLES = 1;
		static constexpr int EXPIRE_MIN_INTERVAL = 30000;

		void enumerateDevices();

		void loadDaemonSleep();

	private:
//		typedef QMap<QString, DS18B20 *> DS18B20DevicesContainer;

//		static int Count(QQmlListProperty<DS18B20> * property);

//		static DS18B20 * At(QQmlListProperty<DS18B20> * property, int index);

		void clearDevices();

//		/**
//		 * Get InputRegister element at specified index of property list. Callback function for QQmlListProperty.
//		 * @return element at index.
//		 */
//		static InputRegister * IrAt(QQmlListProperty<InputRegister> * property, int index);

//		/**
//		 * Get Coil element at specified index of property list. Callback function for QQmlListProperty.
//		 * @return element at index.
//		 */
//		static Coil * BAt(QQmlListProperty<Coil> * property, int index);

//		/**
//		 * Get DiscreteInput element at specified index of property list. Callback function for QQmlListProperty.
//		 * @return element at index.
//		 */
//		static DiscreteInput * IbAt(QQmlListProperty<DiscreteInput> * property, int index);

//		template <typename CONTAINER>
//		void readRegisters(CONTAINER & container, void (Client:: * readFn)(int), const QAtomicInt & run);

//		uint16_t fromClientEndian(uint16_t val) const;

//		uint16_t toClientEndian(uint16_t val) const;

		QString m_connectionName;
		unsigned long m_daemonSleep;
		QVariantMap m_ds18b20;

//		IrDataContainer m_irData;
//		QQmlListProperty<InputRegister> m_ir;
//		RDataContainer m_rData;
//		QQmlListProperty<HoldingRegister> m_r;
//		IbDataContainer m_ibData;
//		QQmlListProperty<DiscreteInput> m_ib;
//		BDataContainer m_bData;
//		QQmlListProperty<Coil> m_b;
//		std::unique_ptr<AbstractConnection> m_connection;
//		endianness_t m_endianness;
//		QSignalMapper * m_rValueRequestMapper;
//		QSignalMapper * m_bValueRequestMapper;
//		QMutex m_rMutex;
//		QMutex m_irMutex;
//		QMutex m_bMutex;
//		QMutex m_ibMutex;
};

//template <typename T>
//T * Client::At(QQmlListProperty<T> * property, int index, void (*onCreate)(QQmlListProperty<T> *, int, T *))
//{
//	typedef typename RegisterTraits<T>::Container Container;
//	Container * propertyData = static_cast<Container *>(property->data);
//	typename Container::iterator it = propertyData->find(index);
//	if (it == propertyData->end()) {
//		it = propertyData->insert(index, new T);
//		if (onCreate != nullptr)
//			onCreate(property, index, *it);
//	}
//	return *it;
//}

//template <typename T>
//int Client::Count(QQmlListProperty<T> * property)
//{
//	Q_UNUSED(property);

//	return std::numeric_limits<int>::max();
//}

//template <typename CONTAINER>
//void Client::readRegisters(CONTAINER & container, void (Client:: * readFn)(int), const QAtomicInt & run)
//{
//	typename CONTAINER::KeysIterator keysIt(container);
//	while (keysIt.hasNext()) {
//		if (!run.load())
//			return;
//		typename CONTAINER::KeysContainer::value_type addr = keysIt.next();
//		if (container.at(addr)->wakeful())
//			(this->*readFn)(addr);
//	}
//}

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
