#include "Coil.hpp"

#include <QtDebug>
#include <QMutexLocker>

namespace cutehmi {
namespace modbus {

Coil::Coil(bool value, QObject * parent):
	QObject(parent),
	m_value(value),
	m_reqValue(value),
	m_awaken(0)
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

void Coil::rest()
{
	m_awaken.fetchAndSubRelaxed(1);
}

void Coil::awake()
{
	m_awaken.fetchAndAddRelaxed(1);
}

bool Coil::wakeful() const
{
	return m_awaken.load();
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
