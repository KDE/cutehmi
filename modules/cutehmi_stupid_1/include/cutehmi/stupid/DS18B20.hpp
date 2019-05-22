#ifndef H_MODULES_CUTEHMI__STUPID__1_INCLUDE_CUTEHMI_STUPID_DS18B20_HPP
#define H_MODULES_CUTEHMI__STUPID__1_INCLUDE_CUTEHMI_STUPID_DS18B20_HPP

#include "internal/common.hpp"

#include <QReadWriteLock>
#include <QVariant>
#include <QAtomicInt>
#include <QDateTime>

namespace cutehmi {
namespace stupid {

class CUTEHMI_STUPID_API DS18B20:
                public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(int error READ error NOTIFY errorChanged)

		enum ValueType : int {
			PLUGGED = 1,
			TEMPERATURE = 2,
			CRC = 4,
			CRC_OK = 8,
			TIMESTAMP = 16,
			EXPIRE = 32
		};
		Q_ENUM(ValueType)

		enum Error : int {
			ERROR_OK = 0,
			ERROR_UNPLUGGED = 1,
			ERROR_WRONG_CRC = 2,
			ERROR_DATA_STALL = 4
		};
		Q_ENUM(Error)

		struct Data
		{
			qint32 temperature = 0;
			bool plugged = false;
			int crc = -1;
			bool crcOK = false;
			QDateTime timestamp;
			QDateTime expire;		///< Expire date as set by client in UTC.
		};

		/**
		 * Constructor.
		 * @param value initial value.
		 * @param parent parent object.
		 */
		explicit DS18B20(QObject * parent = 0);

		int error() const;

		Q_INVOKABLE qint32 temperature() const;

		Q_INVOKABLE bool plugged() const;

		Q_INVOKABLE int crc() const;

		Q_INVOKABLE QDateTime timestamp() const;

		Q_INVOKABLE void rest();

		Q_INVOKABLE void awake();

		Q_INVOKABLE bool wakeful() const;

		const Data & data() const;

	public slots:
		/**
		 * Update data. Appropriate error flags will be set.
		 * @param data new data.
		 *
		 * @threadsafe
		 */
		void updateData(const Data & data);

	signals:
		/**
		 * Value updated. Indicates whether one or more data values have been updated.
		 * @param valueTypes value type flags. Parameter is a binary combination of @p ValueType flags.
		 */
		void valueUpdated(int valueTypes);

		/**
		 * Error changed.
		 */
		void errorChanged();

	private:
		struct Members
		{
			Data data;
			mutable QReadWriteLock dataLock;
			QAtomicInt awaken = 0;
			QAtomicInt error = ERROR_OK;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
