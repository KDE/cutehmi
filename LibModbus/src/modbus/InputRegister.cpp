#include "InputRegister.hpp"
#include "functions.hpp"

#include <QtDebug>
#include <QReadLocker>

namespace cutehmi {
namespace modbus {

InputRegister::InputRegister(uint16_t value, QObject * parent):
	QObject(parent),
	m_value(value),
	m_awaken(0)
{
}

QVariant InputRegister::value(encoding_t encoding) const
{
	QReadLocker locker(& m_valueLock);
	switch (encoding) {
		case INT16:
			return intFromUint16(m_value);
		default:
			qFatal("Unrecognized code (%d) of target encoding.", encoding);
	}
}

void InputRegister::rest()
{
	m_awaken.fetchAndSubRelaxed(1);
}

void InputRegister::awake()
{
	m_awaken.fetchAndAddRelaxed(1);
}

bool InputRegister::wakeful() const
{
	return m_awaken.load();
}

void InputRegister::updateValue(uint16_t value)
{
	m_valueLock.lockForWrite();
	m_value = value;
	m_valueLock.unlock();
	emit valueUpdated();
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
