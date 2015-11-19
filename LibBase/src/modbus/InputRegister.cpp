#include "InputRegister.hpp"

namespace modbus {

InputRegister::InputRegister(qint16 value, QObject * parent):
	QObject(parent),
	m_value(value)
{
}

qint16 InputRegister::value() const
{
	return m_value;
}

void InputRegister::setValue(qint16 value)
{
	if (value != m_value) {
		m_value = value;
		emit valueChanged();
	}
}

}
