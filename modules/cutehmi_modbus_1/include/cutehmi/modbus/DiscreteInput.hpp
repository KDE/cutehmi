#ifndef H_MODULES_CUTEHMI_u_MODBUS_u_1_INCLUDE_CUTEHMI_MODBUS_DISCRETEINPUT_HPP
#define H_MODULES_CUTEHMI_u_MODBUS_u_1_INCLUDE_CUTEHMI_MODBUS_DISCRETEINPUT_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QReadWriteLock>
#include <QAtomicInt>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API DiscreteInput:
	public QObject
{
	Q_OBJECT

	public:
		/**
		 * Constructor.
		 * @param value initial value.
		 * @param parent parent object.
		 */
		explicit DiscreteInput(bool value = false, QObject * parent = 0);

		Q_INVOKABLE bool value() const;

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
		void updateValue(bool value);

	signals:
		void valueUpdated();

	private:
		struct Members
		{
			bool value;
			mutable QReadWriteLock valueLock;
			QAtomicInt awaken;

			Members(bool p_value):
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
