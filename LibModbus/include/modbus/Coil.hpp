#ifndef CUTEHMI_LIBMODBUS_INCLUDE_MODBUS_COIL_HPP
#define CUTEHMI_LIBMODBUS_INCLUDE_MODBUS_COIL_HPP

#include "internal/common.hpp"

#include <QObject>
#include <QMutex>
#include <QReadWriteLock>
#include <QAtomicInt>

namespace cutehmi {
namespace modbus {

class CUTEHMI_MODBUS_API Coil:
	public QObject
{
	Q_OBJECT

	public:
		/**
		 * Constructor.
		 * @param value initial value.
		 * @param parent parent object.
		 */
		explicit Coil(bool value = false, QObject * parent = 0);

		Q_INVOKABLE bool value() const;

		Q_INVOKABLE bool requestedValue() const;

		Q_INVOKABLE void rest();

		Q_INVOKABLE void awake();

		Q_INVOKABLE bool wakeful() const;

		Q_INVOKABLE int pendingRequests() const;

	public slots:
		void requestValue(bool value);

		/**
		 * Update value.
		 * @param value new value.
		 *
		 * @note this function is thread-safe.
		 */
		void updateValue(bool value);

	signals:
		void valueRequested();

		void valueUpdated();

		/**
		 * Value written. This signal is emitted when requested value has been written to the client device.
		 */
		void valueWritten();

	private slots:
		void onValueWritten();

	private:
		struct Members
		{
			bool value;
			mutable QReadWriteLock valueLock;
			bool reqValue;
			mutable QMutex reqValueMutex;
			QAtomicInt awaken;
			int writeCtr;
			mutable QReadWriteLock writeCtrLock;

			Members(bool p_value):
				value(p_value),
				reqValue(p_value),
				awaken(0),
				writeCtr(0)
			{
			}
		};

		utils::MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
