#include <cutehmi/modbus/Register1.hpp>

namespace cutehmi {
namespace modbus {

Register1::Register1(bool value):
	m(new Members{value, 0})
{
}

bool Register1::value() const
{
	return m->value.loadAcquire();
}

void Register1::setValue(bool value)
{
	m->value.storeRelease(value);
}

void Register1::rest()
{
	m->awaken.fetchAndSubRelaxed(1);
}

void Register1::awake()
{
	m->awaken.fetchAndAddRelaxed(1);
}

bool Register1::wakeful() const
{
	return m->awaken.load();
}

}
}
