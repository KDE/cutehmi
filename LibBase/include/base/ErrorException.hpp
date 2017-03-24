#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_ERROREXCEPTION_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_ERROREXCEPTION_HPP

#include "Exception.hpp"
#include "ErrorInfo.hpp"

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API ErrorException:
	public Exception
{
	public:
		template <class ERROR>
		explicit ErrorException(ERROR error);

		const ErrorInfo & info() const;

	private:
		ErrorInfo m_errorInfo;
};

template <class ERROR>
ErrorException::ErrorException(ERROR error):
	Exception(error.str()),
	m_errorInfo(::cutehmi::base::errorInfo<ERROR>(error))
{
}

}
}

#endif
