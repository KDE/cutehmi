#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_ERRORINFO_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_ERRORINFO_HPP

#include <QString>

#include <typeinfo>

#include "Error.hpp"

namespace cutehmi {

/**
 * %Error info.
 *
 * @remark This class is registered as metatype by Initializer instance.
 *
 * @see errorInfo()
 */
struct CUTEHMI_API ErrorInfo
{
	int code;				///< %Error code.
	const char * errClass;	///< %Error class.
	QString str;			///< %Error string.

	/**
	 * %Error info to string.
	 * @return multi-line string containing information extracted from ErrorInfo struct.
	 */
	QString toString() const;
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

Q_DECLARE_METATYPE(cutehmi::ErrorInfo)

#endif

//(c)C: Copyright © 2018-2019, . All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
