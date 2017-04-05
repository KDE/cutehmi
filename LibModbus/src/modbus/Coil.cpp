#include "../../include/modbus/Coil.hpp"

#include <QtDebug>
#include <QMutexLocker>

namespace cutehmi {
namespace modbus {

Coil::Coil(bool value, QObject * parent):
	QObject(parent),
	m(new Members(value))
{
}

bool Coil::value() const
{
	QReadLocker locker(& m->valueLock);
	return m->value;
}

bool Coil::requestedValue() const
{
	QMutexLocker locker(& m->reqValueMutex);
	return m->reqValue;
}

void Coil::rest()
{
	m->awaken.fetchAndSubRelaxed(1);
}

void Coil::awake()
{
	m->awaken.fetchAndAddRelaxed(1);
}

bool Coil::wakeful() const
{
	return m->awaken.load();
}

void Coil::requestValue(bool value)
{
	m->reqValueMutex.lock();
	m->reqValue = value;
	m->reqValueMutex.unlock();
	emit valueRequested();
}

void Coil::updateValue(bool value)
{
	m->valueLock.lockForWrite();
	m->value = value;
	m->valueLock.unlock();
	emit valueUpdated();
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
