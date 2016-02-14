#include "Exception.hpp"

namespace cutehmi {
namespace modbus {

Exception::Exception(const QString & what):
	m_what(what.toLocal8Bit())
{
}

void Exception::raise() const
{
	throw *this;
}

Exception * Exception::clone() const
{
	return new Exception(*this);
}

const char * Exception::what() const noexcept
{
	return m_what.constData();
}

}
}
