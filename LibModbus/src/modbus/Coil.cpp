#include "Coil.hpp"

#include <QtDebug>
#include <QMutexLocker>

namespace cutehmi {
namespace modbus {

Coil::Coil(bool value, QObject * parent):
	QObject(parent),
	m_value(value),
	m_reqValue(value)
{
}

bool Coil::value() const
{
	QReadLocker locker(& m_valueLock);
	return m_value;
}

bool Coil::requestedValue() const
{
	QMutexLocker locker(& m_reqValueMutex);
	return m_reqValue;
}

void Coil::requestValue(bool value)
{
	m_reqValueMutex.lock();
	m_reqValue = value;
	m_reqValueMutex.unlock();
	emit valueRequested();
}

void Coil::updateValue(bool value)
{
	m_valueLock.lockForWrite();
	m_value = value;
	m_valueLock.unlock();
	emit valueUpdated();
}

}
}
