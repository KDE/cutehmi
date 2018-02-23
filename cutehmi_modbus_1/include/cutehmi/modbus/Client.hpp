#ifndef CUTEHMI_CUTEHMI__MODBUS__1__LIB_INCLUDE_MODBUS_CLIENT_HPP
#define CUTEHMI_CUTEHMI__MODBUS__1__LIB_INCLUDE_MODBUS_CLIENT_HPP

#include "internal/common.hpp"
#include "internal/AbstractConnection.hpp"
#include "internal/RegisterTraits.hpp"
#include "AbstractDevice.hpp"

#include <cutehmi/ErrorInfo.hpp>

#include <QObject>
#include <QQmlListProperty>
#include <QHash>
#include <QSignalMapper>
#include <QMutex>

#include <memory>

namespace cutehmi {
namespace modbus {

/**
 * Modbus client.
 */
class CUTEHMI_MODBUS_API Client:
	public AbstractDevice
{
	Q_OBJECT

	public:
		struct CUTEHMI_MODBUS_API Error:
			public cutehmi::Error
		{
			enum : int {
				UNABLE_TO_CONNECT = Error::SUBCLASS_BEGIN,
				FAILED_TO_READ_INPUT_REGISTER,
				FAILED_TO_READ_HOLDING_REGISTER,
				FAILED_TO_WRITE_HOLDING_REGISTER,
				FAILED_TO_READ_DISCRETE_INPUT,
				FAILED_TO_READ_COIL,
				FAILED_TO_WRITE_COIL
			};

			using cutehmi::Error::Error;

			QString str() const;
		};

		explicit Client(std::unique_ptr<internal::AbstractConnection> connection, QObject * parent = 0);

		~Client() override;

		const QQmlListProperty<InputRegister> & ir() override;

		const QQmlListProperty<HoldingRegister> & r() override;

		const QQmlListProperty<DiscreteInput> & ib() override;

		const QQmlListProperty<Coil> & b() override;

		InputRegister * irAt(int index) override;

		HoldingRegister * rAt(int index) override;

		DiscreteInput * ibAt(int index) override;

		Coil * bAt(int index) override;

		bool isConnected() const;

//		void setConnection(std::unique_ptr<internal::AbstractConnection> connection);

		/**
		 * Read input register value and update associated InputRegister object.
		 * @param addr register address.
		 *
		 * @note appropriate InputRegister object must be referenced using @a ir list before using this function.
		 */
		void readIr(int addr);

		/**
		 * Read holding register value and update associated HoldingRegister object.
		 * @param addr register address.
		 *
		 * @note appropriate HoldingRegister object must be referenced using @a r list before using this function.
		 */
		void readR(int addr);

		/**
		 * Write value requested by HoldingRegister object.
		 * @param addr register address.
		 *
		 * @note appropriate HoldingRegister object must be referenced using @a r list before using this function.
		 */
		void writeR(int addr);

		/**
		 * Read discrete input value and update associated DiscreteInput object.
		 * @param addr discrete input address.
		 *
		 * @note appropriate DiscreteInput object must be referenced using @a ib list before using this function.
		 */
		void readIb(int addr);

		/**
		 * Read coil value and update associated Coil object.
		 * @param addr register address.
		 *
		 * @note appropriate Coil object must be referenced using @a b list before using this function.
		 */
		void readB(int addr);

		/**
		 * Write value requested by Coil object.
		 * @param addr register address.
		 *
		 * @note appropriate Coil object must be referenced using @a b list before using this function.
		 */
		void writeB(int addr);

	public slots:
		/**
		 * Connect client to the Modbus device.
		 *
		 * @note this function is thread-safe.
		 */
		void connect();

		/**
		 * Disconnect client from the Modbus device.
		 *
		 * @note this function is thread-safe.
		 */
		void disconnect();

		/**
		 * Read all values of awaken registers and coils.
		 *
		 * @param run indicates whether to interrupt read. Function interrupts reading and returns, if value of @p 0 is being set by another thread.
		 * If @p 1 is set, then function will return only after reading all values of coils and registers.
		 *
		 * @warning this function should be thread-safe, although underlying implementation relies on std::array::at() function. Further investigation
		 * is needed to check whether accessing elements via std::array::at() function is thread-safe.
		 *
		 * "The reference returned can be used to access or modify elements. Concurrently accessing or modifying
		 * different elements is safe." -- http://www.cplusplus.com/reference/array/array/at/.
		 *
		 * What about concurrently accessing same elements? For now use this function with care.
		 */
		void readAll(const QAtomicInt & run = 1);

	signals:
		void error(cutehmi::ErrorInfo errInfo);

		void connected();

		void disconnected();

	protected slots:
		void rValueRequest(int index);

		void bValueRequest(int index);

	private:
		typedef typename internal::RegisterTraits<InputRegister>::Container IrDataContainer;
		typedef typename internal::RegisterTraits<HoldingRegister>::Container RDataContainer;
		typedef typename internal::RegisterTraits<DiscreteInput>::Container IbDataContainer;
		typedef typename internal::RegisterTraits<Coil>::Container BDataContainer;

		/**
		 * Get element at specified index of property list. If element does not exist function creates it.
		 * Generic helper for QQmlListProperty.
		 * @param property property list.
		 * @param index element index.
		 * @param onCreate callback function called (if not @p nullptr) if element has been created. Parameters passed to a callback function are
		 * (@a property, @a index, newly created element).
		 * @return element at index.
		 */
		template <typename T>
		static T * At(QQmlListProperty<T> * property, int index, void (*onCreate)(QQmlListProperty<T> *, int, T *) = nullptr);

		/**
		 * Return number of property list elements. Callback function for QQmlListProperty.
		 * @return number of property list elements.
		 */
		template <typename T>
		static int Count(QQmlListProperty<T> * property);

		/**
		 * Get HoldingRegister element at specified index of property list. Callback function for QQmlListProperty.
		 * @return element at index.
		 */
		static HoldingRegister * RAt(QQmlListProperty<HoldingRegister> * property, int index);

		/**
		 * Get InputRegister element at specified index of property list. Callback function for QQmlListProperty.
		 * @return element at index.
		 */
		static InputRegister * IrAt(QQmlListProperty<InputRegister> * property, int index);

		/**
		 * Get Coil element at specified index of property list. Callback function for QQmlListProperty.
		 * @return element at index.
		 */
		static Coil * BAt(QQmlListProperty<Coil> * property, int index);

		/**
		 * Get DiscreteInput element at specified index of property list. Callback function for QQmlListProperty.
		 * @return element at index.
		 */
		static DiscreteInput * IbAt(QQmlListProperty<DiscreteInput> * property, int index);

		/**
		 * Read all values for the given container.
		 * @param container container to process.
		 * @param readFn. Function to be used to read the value. Function accepts address as a parameter.
		 * @param run allows to interrupt the read if set to @p 0. Normally @p 1.
		 *
		 * @todo optimize reads.
		 */
		template <typename CONTAINER>
		void readRegisters(const CONTAINER & container, void (Client:: * readFn)(int), const QAtomicInt & run);

		struct Members
		{
			IrDataContainer irData;
			QQmlListProperty<InputRegister> ir;
			RDataContainer rData;
			QQmlListProperty<HoldingRegister> r;
			IbDataContainer ibData;
			QQmlListProperty<DiscreteInput> ib;
			BDataContainer bData;
			QQmlListProperty<Coil> b;
			std::unique_ptr<internal::AbstractConnection> connection;
			QSignalMapper * rValueRequestMapper;
			QSignalMapper * bValueRequestMapper;
			QMutex rMutex;
			QMutex irMutex;
			QMutex bMutex;
			QMutex ibMutex;
			QMutex connectionMutex;

			Members(Client * p_client, std::unique_ptr<internal::AbstractConnection> p_connection):
				ir(p_client, & irData, Client::Count<InputRegister>, Client::IrAt),
				r(p_client, & rData, Client::Count<HoldingRegister>, Client::RAt),
				ib(p_client, & ibData, Client::Count<DiscreteInput>, Client::IbAt),
				b(p_client, & bData, Client::Count<Coil>, Client::BAt),
				connection(std::move(p_connection)),
				rValueRequestMapper(new QSignalMapper(p_client)),
				bValueRequestMapper(new QSignalMapper(p_client))
			{
			}
		};

		MPtr<Members> m;
};

template <typename T>
T * Client::At(QQmlListProperty<T> * property, int index, void (*onCreate)(QQmlListProperty<T> *, int, T *))
{
	typedef typename internal::RegisterTraits<T>::Container Container;
	Container * propertyData = static_cast<Container *>(property->data);
	typename Container::iterator it = propertyData->find(index);
	if (it == propertyData->end()) {
		it = propertyData->insert(index, new T);
		if (onCreate != nullptr)
			onCreate(property, index, *it);
	}
	return *it;
}

template <typename T>
int Client::Count(QQmlListProperty<T> * property)
{
	Q_UNUSED(property);

	return std::numeric_limits<int>::max();
}

template <typename CONTAINER>
void Client::readRegisters(const CONTAINER & container, void (Client:: * readFn)(int), const QAtomicInt & run)
{
	typename CONTAINER::KeysIterator keysIt(container);
	while (keysIt.hasNext()) {
		if (!run.load())
			return;
		typename CONTAINER::KeysContainer::value_type addr = keysIt.next();
		if (container.at(addr)->wakeful())
			(this->*readFn)(addr);
	}
}

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
