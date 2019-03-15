#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_ERROREXCEPTION_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_ERROREXCEPTION_HPP

#include "ExceptionMixin.hpp"
#include "ErrorInfo.hpp"

namespace cutehmi {

/**
 * %Error exception.
 */
class CUTEHMI_API ErrorException:
	public ExceptionMixin<ErrorException>
{
	typedef ExceptionMixin<ErrorException> Parent;

	public:
		template <class ERR>
		explicit ErrorException(ERR error);

		const ErrorInfo & info() const;

	private:
		ErrorInfo m_errorInfo;
};

template <class ERR>
ErrorException::ErrorException(ERR error):
	Parent(error.str()),
	m_errorInfo(::cutehmi::errorInfo<ERR>(error))
{
}

}

#endif
﻿
//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
