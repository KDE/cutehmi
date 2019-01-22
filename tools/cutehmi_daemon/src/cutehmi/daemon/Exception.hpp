#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

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

#endif // EXCEPTION_HPP
