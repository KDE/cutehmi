#include "HoldingRegister.hpp"
#include "functions.hpp"

#include <QtDebug>
#include <QMutexLocker>

namespace cutehmi {
namespace modbus {

HoldingRegister::HoldingRegister(uint16_t value, QObject * parent):
	QObject(parent),
	m_value(value),
	m_reqValue(value)
{
}

qint16 HoldingRegister::int16() const
{
	qDebug("deprecated don't use this function, int16 property will be removed.");
	return m_value;
}

void HoldingRegister::setInt16(qint16 value)
{
	qDebug("deprecated don't use this function, int16 property will be removed.");
	if (value != m_value) {
		m_value = value;
//		emit valueChanged();
	}
}

QVariant HoldingRegister::value(encoding_t encoding) const
{
	QReadLocker locker(& m_valueLock);
	switch (encoding) {
		case INT16:
			return intFromUint16(m_value);
		default:
			qFatal("Unrecognized code (%d) of target encoding.", encoding);
	}
}

uint16_t HoldingRegister::requestedValue() const
{
	QMutexLocker locker(& m_reqValueMutex);
	return m_reqValue;
}

void HoldingRegister::requestValue(QVariant value, encoding_t encoding)
{
	switch (encoding) {
		case INT16:
			m_reqValueMutex.lock();
			m_reqValue = intToUint16(value.toInt());
			m_reqValueMutex.unlock();
			emit valueRequested();
			break;
		default:
			qFatal("Unrecognized code (%d) of target encoding.", encoding);
	}
}

void HoldingRegister::updateValue(uint16_t value)
{
	m_valueLock.lockForWrite();
	m_value = value;
	m_valueLock.unlock();
	emit valueUpdated();
}

}
}
