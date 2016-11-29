#include "DiscreteInput.hpp"

#include <QtDebug>
#include <QReadLocker>

namespace cutehmi {
namespace modbus {

DiscreteInput::DiscreteInput(bool value, QObject * parent):
	QObject(parent),
	m_value(value),
	m_awaken(0)
{
}

bool DiscreteInput::value() const
{
	QReadLocker locker(& m_valueLock);
	return m_value;
}

void DiscreteInput::rest()
{
	m_awaken.fetchAndSubRelaxed(1);
}

void DiscreteInput::awake()
{
	m_awaken.fetchAndAddRelaxed(1);
}

bool DiscreteInput::wakeful() const
{
	return m_awaken.load();
}

void DiscreteInput::updateValue(bool value)
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
