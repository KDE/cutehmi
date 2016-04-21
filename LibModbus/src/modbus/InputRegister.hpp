#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_INPUTREGISTER_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_INPUTREGISTER_HPP

#include "../platform.hpp"

#include <QObject>
#include <QReadWriteLock>
#include <QVariant>

namespace cutehmi {
namespace modbus {

/**
 * Modbus input register.
 *
 * @note to make this class accessible from QML it must inherit after QObject,
 * thus keep in mind that this class is relatively heavy.
 */
class CUTEHMI_MODBUS_API InputRegister:
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
		explicit InputRegister(uint16_t value = 0, QObject * parent = 0);

		Q_INVOKABLE QVariant value(encoding_t encoding = INT16) const;

	public slots:
		/**
		 * Update value.
		 * @param value new value.
		 *
		 * @note this function is thread-safe.
		 */
		void updateValue(uint16_t value);

	signals:
		void valueUpdated();

	private:
		uint16_t m_value;
		mutable QReadWriteLock m_valueLock;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
