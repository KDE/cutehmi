#include "InputRegister.hpp"

namespace modbus {

InputRegister::InputRegister(qint16 value, QObject * parent):
	QObject(parent),
	m_value(value)
{
}

qint16 InputRegister::int16() const
{
	return m_value;
}

void InputRegister::setInt16(qint16 value)
{
	if (value != m_value) {
		m_value = value;
		emit valueChanged();
	}
}

}
