#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_HOLDINGREGISTER_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_HOLDINGREGISTER_HPP

#include "../platform.hpp"

#include <QObject>
#include <QMutex>
#include <QReadWriteLock>
#include <QVariant>

namespace cutehmi {
namespace modbus {

/**
 * Modbus holding register. This class represents Modbus holding registers.
 * According to Modbus specification each holding register holds 16 bit data.
 * Objects of this class act as a convenient proxy between instances of QML HoldingRegisterItem and Client.
 *
 * @note to make this class accessible from QML it must inherit after QObject,
 * thus keep in mind that this class is relatively heavy.
 */
class CUTEHMI_MODBUS_API HoldingRegister:
	public QObject
{
	Q_OBJECT

	public:
		enum encoding_t {
			INT16
		};
		Q_ENUM(encoding_t)

		/**
		 * Constructor.
		 * @param value initial value.
		 * @param parent parent object.
		 */
		explicit HoldingRegister(uint16_t int16 = 0, QObject * parent = 0);

		Q_INVOKABLE QVariant value(encoding_t encoding = INT16) const;

		Q_INVOKABLE uint16_t requestedValue() const;

	public slots:
		void requestValue(QVariant value, encoding_t encoding = INT16);

		/**
		 * Update value.
		 * @param value new value.
		 *
		 * @note this function is thread-safe.
		 */
		void updateValue(uint16_t value);

	signals:
		void valueRequested();

		void valueUpdated();

		/**
		 * Request value written. This signal is emitted when requested value has been written to the client device.
		 */
		void valueWritten();

	private:
		uint16_t m_value;
		mutable QReadWriteLock m_valueLock;
		uint16_t m_reqValue;
		mutable QMutex m_reqValueMutex;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
