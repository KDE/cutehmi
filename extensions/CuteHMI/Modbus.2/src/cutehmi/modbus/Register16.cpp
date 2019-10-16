#include <cutehmi/modbus/Register16.hpp>

namespace cutehmi {
namespace modbus {

Register16::Register16(quint16 value):
	m(new Members{value, 0})
{
}

quint16 Register16::value() const
{
	return m->value.loadAcquire();
}

void Register16::setValue(quint16 value)
{
	m->value.storeRelease(value);
}

void Register16::rest()
{
	m->awaken.fetchAndSubRelaxed(1);
}

void Register16::awake()
{
	m->awaken.fetchAndAddRelaxed(1);
}

bool Register16::wakeful() const
{
	return m->awaken.load();
}

}
}
