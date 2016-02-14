#include "ExtError.hpp"

namespace cutehmi {
namespace base {

ExtError::ExtError(int code, const QString & details):
	Error(code),
	m_details(details)
{
}

QString ExtError::details() const
{
	return m_details;
}

void ExtError::setDetails(const QString & details)
{
	m_details = details;
}

}
}
