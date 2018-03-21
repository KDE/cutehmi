#include "../../../include/cutehmi/modbus/internal/functions.hpp"
#include "../../../include/cutehmi/modbus/InputRegister.hpp"
#include "../../../include/cutehmi/modbus/Exception.hpp"

#include <QtDebug>
#include <QReadLocker>

namespace cutehmi {
namespace modbus {

InputRegister::InputRegister(uint16_t value, QObject * parent):
	QObject(parent),
	m(new Members(value))
{
}

QVariant InputRegister::value(Encoding encoding) const noexcept(false)
{
	QReadLocker locker(& m->valueLock);
	switch (encoding) {
		case INT16:
			return internal::intFromUint16(m->value);
		default:
			throw Exception(QObject::tr("Unrecognized encoding code ('%1').").arg(encoding));
	}
}

void InputRegister::rest()
{
	m->awaken.fetchAndSubRelaxed(1);
}

void InputRegister::awake()
{
	m->awaken.fetchAndAddRelaxed(1);
}

bool InputRegister::wakeful() const
{
	return m->awaken.load();
}

void InputRegister::updateValue(uint16_t value)
{
	m->valueLock.lockForWrite();
	m->value = value;
	m->valueLock.unlock();
	emit valueUpdated();
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
