#include "../../include/modbus/DiscreteInput.hpp"

#include <QtDebug>
#include <QReadLocker>

namespace cutehmi {
namespace modbus {

DiscreteInput::DiscreteInput(bool value, QObject * parent):
	QObject(parent),
	m(new Members(value))
{
}

bool DiscreteInput::value() const
{
	QReadLocker locker(& m->valueLock);
	return m->value;
}

void DiscreteInput::rest()
{
	m->awaken.fetchAndSubRelaxed(1);
}

void DiscreteInput::awake()
{
	m->awaken.fetchAndAddRelaxed(1);
}

bool DiscreteInput::wakeful() const
{
	return m->awaken.load();
}

void DiscreteInput::updateValue(bool value)
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
