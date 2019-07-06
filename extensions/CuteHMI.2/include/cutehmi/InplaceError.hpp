#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_INPLACEERROR_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_INPLACEERROR_HPP

#include "internal/common.hpp"

#include "Error.hpp"

namespace cutehmi {

/**
 * In-place error.
 *
 * @remark This class is registered as metatype by Initializer instance.
 */
struct CUTEHMI_API InplaceError:
	public Error
{
	// Note: line count starts with 1.
	InplaceError(const QString & message = "Error.", const char * file = nullptr, int line = 0, const char * function = nullptr, int code = Error::FAIL);

	QString str() const;

	QString message;
	const char * file;
	int line;
	const char * function;
};

}

#define CUTEHMI_ERROR(MESSAGE) cutehmi::InplaceError(MESSAGE, __FILE__, __LINE__, Q_FUNC_INFO)

Q_DECLARE_METATYPE(cutehmi::InplaceError)

#endif
