#ifndef H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_EXCEPTION_HPP
#define H_TOOLS_CUTEHMI_u_DAEMON_SRC_CUTEHMI_DAEMON_EXCEPTION_HPP

#include <cutehmi/ExceptionMixin.hpp>

namespace cutehmi {
namespace daemon {

class Exception:
	public ExceptionMixin<Exception>
{
	typedef ExceptionMixin<Exception> Parent;

	public:
		Exception(const QString & what);
};

}
}

#endif
