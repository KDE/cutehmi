#include "InputRegister.hpp"

namespace cutehmi {
namespace modbus {

InputRegister::InputRegister(uint16_t value, QObject * parent):
	QObject(parent),
	m_value(value)
{
}

qint16 InputRegister::int16() const
{
	qWarning("InputRegister::int16() will be removed");
	return m_value;
}

void InputRegister::setInt16(qint16 value)
{
	qWarning("InputRegister::setInt16() will be removed");
	if (value != m_value) {
		m_value = value;
		emit valueChanged();
	}
}

void InputRegister::updateValue(uint16_t value)
{
	QMutexLocker locker(& m_valueMutex);
	m_value = value;
	emit valueUpdated();
}

}
}
