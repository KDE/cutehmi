#ifndef H_MODULES_CUTEHMI_u_MODBUS_u_1_INCLUDE_CUTEHMI_MODBUS_INPUTREGISTER_HPP
#define H_MODULES_CUTEHMI_u_MODBUS_u_1_INCLUDE_CUTEHMI_MODBUS_INPUTREGISTER_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QReadWriteLock>
#include <QVariant>
#include <QAtomicInt>

namespace cutehmi {
namespace modbus {

/**
 * Modbus input register.
 *
 * @note To make this class accessible from QML it must inherit after QObject,
 * thus keep in mind that this class is relatively heavy.
 */
class CUTEHMI_MODBUS_API InputRegister:
	public QObject
{
	Q_OBJECT

	public:
		enum Encoding {
			INT16
		};
		Q_ENUM(Encoding)

		/**
		 * Constructor.
		 * @param value initial value.
		 * @param parent parent object.
		 */
		explicit InputRegister(uint16_t value = 0, QObject * parent = 0);

		Q_INVOKABLE QVariant value(Encoding encoding = INT16) const noexcept(false);

		Q_INVOKABLE void rest();

		Q_INVOKABLE void awake();

		Q_INVOKABLE bool wakeful() const;

	public slots:
		/**
		 * Update value.
		 * @param value new value.
		 *
		 * @threadsafe
		 */
		void updateValue(uint16_t value);

	signals:
		void valueUpdated();

	private:
		struct Members
		{
			uint16_t value;
			mutable QReadWriteLock valueLock;
			QAtomicInt awaken;

			Members(uint16_t p_value):
				value(p_value),
				awaken(0)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
