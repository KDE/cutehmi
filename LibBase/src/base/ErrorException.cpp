#include "../../include/base/ErrorException.hpp"

namespace cutehmi {
namespace base {

const ErrorInfo & ErrorException::info() const
{
	return m_errorInfo;
}

}
}
