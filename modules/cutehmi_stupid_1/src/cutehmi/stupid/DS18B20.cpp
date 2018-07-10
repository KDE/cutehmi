#include "../../../include/cutehmi/stupid/DS18B20.hpp"

namespace cutehmi {
namespace stupid {

DS18B20::DS18B20(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

int DS18B20::error() const
{
	return m->error.load();
}

//QVariant DS18B20::value(ValueType type) const
//{
//	QReadLocker locker(& m->dataLock);
//	switch (type) {
//		case PLUGGED:
//			return m->data.plugged;
//		case TEMPERATURE:
//			return m->data.temperature;
//		case CRC:
//			return m->data.crc;
//		case CRC_OK:
//			return m->data.crcOK;
//		case TIMESTAMP:
//			return m->data.timestamp;	/// @todo probably convert to integral
//		default:
//			qFatal("Unrecognized code (%d) of value type.", type);
//	}

//}

qint32 DS18B20::temperature() const
{
	QReadLocker locker(& m->dataLock);
	return m->data.temperature;
}

bool DS18B20::plugged() const
{
	QReadLocker locker(& m->dataLock);
	return m->data.plugged;
}

int DS18B20::crc() const
{
	QReadLocker locker(& m->dataLock);
	return m->data.crc;
}

QDateTime DS18B20::timestamp() const
{
	QReadLocker locker(& m->dataLock);
	return m->data.timestamp;
}

void DS18B20::rest()
{
	m->awaken.fetchAndSubRelaxed(1);
}

void DS18B20::awake()
{
	m->awaken.fetchAndAddRelaxed(1);
}

bool DS18B20::wakeful() const
{
	return m->awaken.load();
}

const DS18B20::Data & DS18B20::data() const
{
	return m->data;
}

void DS18B20::updateData(const Data & data)
{
	int error = ERROR_OK;
	if (!data.crcOK)
		error |= ERROR_WRONG_CRC;
	if (!data.plugged)
		error |= ERROR_UNPLUGGED;
	if (data.expire < QDateTime::currentDateTimeUtc())
		error |= ERROR_DATA_STALL;

	m->dataLock.lockForWrite();
	m->data = data;
	m->dataLock.unlock();
	emit valueUpdated(PLUGGED | TEMPERATURE | CRC | CRC_OK | TIMESTAMP | EXPIRE);

	if (error != m->error.load()) {
		m->error.store(error);
		emit errorChanged();
	}
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
