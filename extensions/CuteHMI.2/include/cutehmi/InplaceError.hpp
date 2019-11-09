#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_INPLACEERROR_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_INPLACEERROR_HPP

#include "internal/common.hpp"

#include "Error.hpp"

namespace cutehmi {

/**
 * In-place error. This class can be more conveniently used with CUTEHMI_ERROR macro.
 *
 * @remark This class is registered as metatype by Initializer instance.
 */
struct CUTEHMI_API InplaceError:
	public Error
{
	/**
	 * Constructor.
	 * @param message error message.
	 * @param file file name, where error occurred.
	 * @param line line at which error occurred.
	 * @param function function inside which error occurred.
	 * @param code error code.
	 *
	 * @note It is not intended to use this constructor directly. To conveniently create an instance of this class a CUTEHMI_ERROR
	 * macro, which takes only message as an argument, should be used.
	 *
	 * @internal Line count starts with 1.
	 */
	InplaceError(const QString & message = "Error.", const char * file = nullptr, int line = 0, const char * function = nullptr, int code = Error::FAIL);

	/**
	 * Get error string.
	 * @return error string.
	 */
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

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
