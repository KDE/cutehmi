#ifndef CUTEHMI_LIBBASE_SRC_BASE_ERRORINFO_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_ERRORINFO_HPP

#include <QString>

#include <typeinfo>

#include "Error.hpp"

namespace cutehmi {
namespace base {

struct ErrorInfo
{
	int code;				///< Error code.
	const char * errClass;	///< Error class.
	QString str;			///< Error string.
};

/**
 * Get error info. Produces ErrorInfo from instance of Error or its subclass.
 * @param err instance of Error class or its subclass.
 * @return error info structure.
 */
template <typename ERR>
ErrorInfo errorInfo(ERR err)
{
	return ErrorInfo{err.code(), typeid(ERR).name(), err.str()};
}

}
}

#endif

