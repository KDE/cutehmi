#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_ERROREXCEPTION_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_ERROREXCEPTION_HPP

#include "ExceptionMixin.hpp"
#include "ErrorInfo.hpp"

namespace cutehmi {

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

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
