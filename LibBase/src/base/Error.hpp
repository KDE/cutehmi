#ifndef CUTEHMI_LIBBASE_SRC_BASE_ERROR_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_ERROR_HPP

#include "../platform.hpp"

#include <QString>
#include <QCoreApplication>

namespace base {

/**
 * Standarized error. Class reserves negative values for its error codes. When subclassing start
 * custom error codes from 1 (@P Error::SUBCLASS_BEGIN).
 */
struct CUTEHMI_BASE_API Error
{
	Q_DECLARE_TR_FUNCTIONS(base::Error) // This macro ends with "private:" specifier :o !!!

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
		 * @param p_code error code.
		 */
		Error(int p_code);

		/**
		 * Conversion to @p int.
		 */
		operator int() const;

		/**
		 * Check if error code is @p Error::OK.
		 * @return @p true when error code is @p Error::OK, @p false otherwise.
		 */
		bool success() const;

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
		int code;
};

}

#endif
