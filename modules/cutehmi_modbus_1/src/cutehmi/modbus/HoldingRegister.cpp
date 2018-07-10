#include "../../../include/cutehmi/modbus/internal/functions.hpp"
#include "../../../include/cutehmi/modbus/HoldingRegister.hpp"
#include "../../../include/cutehmi/modbus/Exception.hpp"

#include <QtDebug>
#include <QMutexLocker>
#include <QReadLocker>

namespace cutehmi {
namespace modbus {

HoldingRegister::HoldingRegister(uint16_t value, QObject * parent):
	QObject(parent),
	m(new Members(value))
{
	connect(this, & HoldingRegister::valueWritten, this, & HoldingRegister::onValueWritten);
	connect(this, & HoldingRegister::valueRejected, this, & HoldingRegister::onValueRejected);
}

QVariant HoldingRegister::value(Encoding encoding) const noexcept(false)
{
	QReadLocker locker(& m->valueLock);
	switch (encoding) {
		case INT16:
			return internal::intFromUint16(m->value);
		default:
			throw Exception(QObject::tr("Unrecognized encoding code ('%1').").arg(encoding));
	}
}

uint16_t HoldingRegister::requestedValue() const
{
	QMutexLocker locker(& m->reqValueMutex);
	return m->reqValue;
}

void HoldingRegister::rest()
{
	m->awaken.fetchAndSubRelaxed(1);
}

void HoldingRegister::awake()
{
	m->awaken.fetchAndAddRelaxed(1);
}

bool HoldingRegister::wakeful() const
{
	return m->awaken.load();
}

int HoldingRegister::pendingRequests() const
{
	QReadLocker locker(& m->writeCtrLock);
	return m->writeCtr;
}

void HoldingRegister::requestValue(QVariant value, Encoding encoding) noexcept(false)
{
	m->writeCtrLock.lockForWrite();
	m->writeCtr++;
	m->writeCtrLock.unlock();
	switch (encoding) {
		case INT16:
			m->reqValueMutex.lock();
			m->reqValue = internal::intToUint16(value.toInt());
			m->reqValueMutex.unlock();
			emit valueRequested();
			break;
		default:
			m->writeCtrLock.lockForWrite();
			m->writeCtr--;
			m->writeCtrLock.unlock();
			throw Exception(QObject::tr("Unrecognized encoding code ('%1').").arg(encoding));
	}
}

void HoldingRegister::updateValue(uint16_t value)
{
	m->valueLock.lockForWrite();
	m->value = value;
	m->valueLock.unlock();
	emit valueUpdated();
}

void HoldingRegister::onValueWritten()
{
	m->writeCtrLock.lockForWrite();
	m->writeCtr--;
	m->writeCtrLock.unlock();
}

void HoldingRegister::onValueRejected()
{
	m->writeCtrLock.lockForWrite();
	m->writeCtr--;
	m->writeCtrLock.unlock();
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
