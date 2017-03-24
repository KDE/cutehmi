#include "../../include/base/Exception.hpp"

namespace cutehmi {
namespace base {

Exception::Exception(const QString & what):
	m_whatArr(what.toLocal8Bit())
{
}

const char * Exception::what() const noexcept
{
	return m_whatArr.constData();
}

}
}
