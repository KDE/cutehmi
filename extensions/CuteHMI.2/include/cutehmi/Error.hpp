#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_ERROR_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_ERROR_HPP

#include "internal/platform.hpp"

#include <QString>
#include <QCoreApplication>

namespace cutehmi {

/**
 * Standarized error. Class reserves negative values for its error codes. When subclassing start
 * custom error codes from 1 (@p Error::SUBCLASS_BEGIN).
 */
struct CUTEHMI_API Error
{
	Q_DECLARE_TR_FUNCTIONS(cutehmi::Error) // This macro ends with "private:" specifier :o !!!

	public:
		enum : int {
			UNINITIALIZED = -2,
			FAIL = -1,
			OK = 0,
			SUBCLASS_BEGIN = 1
		};

		/**
		 * Default constructor.
		 */
		Error();

		/**
		 * Conversion constructor.
		 * @param code error code.
		 */
		Error(int code);

		bool operator ==(const Error & other) const;

		bool operator !=(const Error & other) const;

		/**
		 * Conversion to @p bool. Evaluates to @p true if error code is @p Error::OK, @p false otherwise.
		 */
		operator bool() const;

		/**
		 * Get error code.
		 * @return error code.
		 */
		int code() const;

		/**
		 * Get error string. A subclass may reimplement this method to provide
		 * its own error descriptions.
		 * @return error message.
		 *
		 * @note This function is non-virtual. When calling this function on down-casted
		 * instance of derived class, it may not recognize error code and return
		 * generic message.
		 */
		QString str() const;

	protected:
		void setCode(int code);

	private:
		int m_code;
};

}

CUTEHMI_API bool operator ==(const cutehmi::Error & error, int code);

CUTEHMI_API bool operator ==(int code, const cutehmi::Error & error);

CUTEHMI_API bool operator !=(const cutehmi::Error & error, int code);

CUTEHMI_API bool operator !=(int code, const cutehmi::Error & error);

#endif

//(c)C: Copyright © 2018-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
