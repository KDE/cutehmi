#include "Exception.hpp"

namespace modbus {

Exception::Exception(const QString & what, const QString & details):
	m_what(what.toLocal8Bit()),
	m_details(details.toLocal8Bit())
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

const char * Exception::details() const noexcept
{
	return m_details.constData();
}

bool Exception::hasDetails() const
{
	return !m_details.isEmpty();
}

}
