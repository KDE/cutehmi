#ifndef CUTEHMI_LIBBASE_SRC_BASE_EXTERROR_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_EXTERROR_HPP

#include "Error.hpp"

namespace cutehmi {
namespace base {

struct CUTEHMI_BASE_API ExtError:
	public Error
{
	public:
		using Error::Error;

		/**
		 * Constructor.
		 * @param code error code.
		 * @param details error details.
		 */
		ExtError(int code, const QString & details);

		ExtError(const ExtError & other) = default;

		QString details() const;

		void setDetails(const QString & details);

	private:
		QString m_details;
};

}
}

#endif
