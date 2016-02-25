#include "InputRegister.hpp"

namespace cutehmi {
namespace modbus {

InputRegister::InputRegister(uint16_t value, QObject * parent):
	QObject(parent),
	m_value(value)
{
}

void InputRegister::updateValue(uint16_t value)
{
	QMutexLocker locker(& m_valueMutex);
	m_value = value;
	emit valueUpdated();
}

}
}
