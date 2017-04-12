#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_ERROR_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_ERROR_HPP

#include "internal/platform.hpp"

#include <QString>
#include <QCoreApplication>

namespace cutehmi {
namespace base {

/**
 * Standarized error. Class reserves negative values for its error codes. When subclassing start
 * custom error codes from 1 (@p Error::SUBCLASS_BEGIN).
 */
struct CUTEHMI_BASE_API Error
{
	Q_DECLARE_TR_FUNCTIONS(cutehmi::base::Error) // This macro ends with "private:" specifier :o !!!

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
		 * @note this function is non-virtual. When calling this function on down-casted
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
}

CUTEHMI_BASE_API bool operator ==(const cutehmi::base::Error & error, int code);

CUTEHMI_BASE_API bool operator ==(int code, const cutehmi::base::Error & error);

CUTEHMI_BASE_API bool operator !=(const cutehmi::base::Error & error, int code);

CUTEHMI_BASE_API bool operator !=(int code, const cutehmi::base::Error & error);

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
