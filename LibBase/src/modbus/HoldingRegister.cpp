#include "HoldingRegister.hpp"

namespace modbus {

HoldingRegister::HoldingRegister(qint16 value, QObject * parent):
	QObject(parent),
	m_value(value)
{
}

qint16 HoldingRegister::int16() const
{
	return m_value;
}

void HoldingRegister::setInt16(qint16 value)
{
	if (value != m_value) {
		m_value = value;
		emit valueChanged();
	}
}

}
