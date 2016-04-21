#include "DiscreteInput.hpp"

#include <QtDebug>
#include <QReadLocker>

namespace cutehmi {
namespace modbus {

DiscreteInput::DiscreteInput(bool value, QObject * parent):
	QObject(parent),
	m_value(value)
{
}

bool DiscreteInput::value() const
{
	QReadLocker locker(& m_valueLock);
	return m_value;
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
