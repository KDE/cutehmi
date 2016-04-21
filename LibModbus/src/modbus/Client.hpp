#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_CLIENT_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_CLIENT_HPP

#include "RegisterTraits.hpp"

#include <base/ErrorInfo.hpp>

#include <QObject>
#include <QQmlListProperty>
#include <QHash>
#include <QSignalMapper>
#include <QMutex>

#include <memory>

namespace cutehmi {
namespace modbus {

class AbstractConnection;

/**
 * Modbus client.
 */
class CUTEHMI_MODBUS_API Client:
	public QObject
{
	Q_OBJECT
	Q_PROPERTY(QQmlListProperty<cutehmi::modbus::InputRegister> ir READ ir NOTIFY irChanged)
	Q_PROPERTY(QQmlListProperty<cutehmi::modbus::HoldingRegister> r READ r NOTIFY rChanged)
	Q_PROPERTY(QQmlListProperty<cutehmi::modbus::DiscreteInput> ib READ ib NOTIFY ibChanged)
	Q_PROPERTY(QQmlListProperty<cutehmi::modbus::Coil> b READ b NOTIFY bChanged)
//remember to delete container elements!!!
//32 bit registers/16 bit addressing	(alternatively idr/dr (double register, then could be qr - quad for 64 bit)
//	Q_PROPERTY(QQmlListProperty<cutehmi::modbus::InputRegister> irr READ irr NOTIFY irChanged)
//	Q_PROPERTY(QQmlListProperty<cutehmi::modbus::HoldingRegister> rr READ rr NOTIFY rChanged)

	public:
		struct CUTEHMI_MODBUS_API Error:
			public base::Error
		{
			enum : int {
				UNABLE_TO_CONNECT = base::Error::SUBCLASS_BEGIN
			};

			using base::Error::Error;

			QString str() const;
		};

		enum endianness_t {
			ENDIAN_BIG,
			ENDIAN_LITTLE
		};

		static const endianness_t INITIAL_ENDIANNESS = ENDIAN_BIG;

		explicit Client(std::unique_ptr<AbstractConnection> connection, QObject * parent = 0);

		~Client() override;

		void setEndianness(endianness_t endianness);

		endianness_t endianness() const;

		const QQmlListProperty<InputRegister> & ir() const;

		const QQmlListProperty<HoldingRegister> & r() const;

		const QQmlListProperty<DiscreteInput> & ib() const;

		const QQmlListProperty<Coil> & b() const;

//		void setConnection(std::unique_ptr<AbstractConnection> connection);

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
		 */
		void connect();

		/**
		 * Disconnect client from the Modbus device.
		 */
		void disconnect();

		/**
		 * Read all values of registers and coils.
		 *
		 * @internal It may be desirable to provide "sleeping registers" optimization in future. Sleeping registers
		 * would be excluded from update of their values. For example, when indicator is not visible it does not
		 * make sense to read its value.
		 */
		void readAll();

	signals:
		void error(base::ErrorInfo errInfo);

		void connected();

		void disconnected();

		void irChanged();

		void rChanged();

		void ibChanged();

		void bChanged();

	protected slots:
		void rValueRequest(int index);

		void bValueRequest(int index);

	private:
		typedef typename RegisterTraits<InputRegister>::Container IrDataContainer; ///< Holds (address, register) pairs. @note Qt uses int type for sizes and indices.
		typedef typename RegisterTraits<HoldingRegister>::Container RDataContainer; ///< Holds (address, register) pairs. @note Qt uses int type for sizes and indices.
		typedef typename RegisterTraits<DiscreteInput>::Container IbDataContainer; ///< Holds (address, register) pairs. @note Qt uses int type for sizes and indices.
		typedef typename RegisterTraits<Coil>::Container BDataContainer; ///< Holds (address, register) pairs. @note Qt uses int type for sizes and indices.

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

		uint16_t fromClientEndian(uint16_t val) const;

		uint16_t toClientEndian(uint16_t val) const;

		IrDataContainer m_irData;
		QQmlListProperty<InputRegister> m_ir;
		RDataContainer m_rData;
		QQmlListProperty<HoldingRegister> m_r;
		IbDataContainer m_ibData;
		QQmlListProperty<DiscreteInput> m_ib;
		BDataContainer m_bData;
		QQmlListProperty<Coil> m_b;
		std::unique_ptr<AbstractConnection> m_connection;
		endianness_t m_endianness;
		QSignalMapper * m_rValueRequestMapper;
		QSignalMapper * m_bValueRequestMapper;
		QMutex m_rMutex;
		QMutex m_irMutex;
		QMutex m_bMutex;
		QMutex m_ibMutex;
};

template <typename T>
T * Client::At(QQmlListProperty<T> * property, int index, void (*onCreate)(QQmlListProperty<T> *, int, T *))
{
	typedef typename RegisterTraits<T>::Container Container;
	Container * propertyData = static_cast<Container *>(property->data);
	typename Container::iterator it = propertyData->find(index);
	if (it == propertyData->end()) {
		it = propertyData->insert(index, new T);
		if (onCreate != nullptr)
			onCreate(property, index, it.value());
	}
	return it.value();
}

template <typename T>
int Client::Count(QQmlListProperty<T> * property)
{
	Q_UNUSED(property);

	return std::numeric_limits<int>::max();
}

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
