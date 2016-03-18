#include "InputRegister.hpp"

namespace cutehmi {
namespace modbus {

InputRegister::InputRegister(uint16_t value, QObject * parent):
	QObject(parent),
	m_value(value)
{
}

void InputRegister::updateValue(uint16_t value)
{
	QMutexLocker locker(& m_valueMutex);
	m_value = value;
	emit valueUpdated();
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
