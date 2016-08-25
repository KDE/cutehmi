#ifndef CUTEHMI_LIBSTUPID_SRC_STUPID_CLIENT_HPP
#define CUTEHMI_LIBSTUPID_SRC_STUPID_CLIENT_HPP

#include "../platform.hpp"

#include <QObject>
#include <QSqlDatabase>

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
//	Q_PROPERTY(QQmlListProperty<cutehmi::stupid::DS18B20> ds18b20 READ ds18b20 NOTIFY ds18b20Changed)

	public:
		explicit Client(std::unique_ptr<QSqlDatabase> db, QObject * parent = 0);

//		const QQmlListProperty<DS18B20> & ds18b20() const;

//		void setConnection(std::unique_ptr<AbstractConnection> connection);

		/**
		 * Read input register value and update associated InputRegister object.
		 * @param addr register address.
		 *
		 * @note appropriate InputRegister object must be referenced using @a ir list before using this function.
		 */
//		void readDS18B20(const QString & id);

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
//		void readAll(const QAtomicInt & run = 1);

	private:
//		typedef typename RegisterTraits<DS18B20>::Container DS18B20DataContainer;

//		/**
//		 * Get element at specified index of property list. If element does not exist function creates it.
//		 * Generic helper for QQmlListProperty.
//		 * @param property property list.
//		 * @param index element index.
//		 * @param onCreate callback function called (if not @p nullptr) if element has been created. Parameters passed to a callback function are
//		 * (@a property, @a index, newly created element).
//		 * @return element at index.
//		 */
//		template <typename T>
//		static T * At(QQmlListProperty<T> * property, int index, void (*onCreate)(QQmlListProperty<T> *, int, T *) = nullptr);

//		/**
//		 * Return number of property list elements. Callback function for QQmlListProperty.
//		 * @return number of property list elements.
//		 */
//		template <typename T>
//		static int Count(QQmlListProperty<T> * property);

//		/**
//		 * Get HoldingRegister element at specified index of property list. Callback function for QQmlListProperty.
//		 * @return element at index.
//		 */
//		static HoldingRegister * RAt(QQmlListProperty<HoldingRegister> * property, int index);

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

		std::unique_ptr<QSqlDatabase> m_db;

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
