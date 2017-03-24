#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_EXCEPTION_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_EXCEPTION_HPP

#include "internal/common.hpp"

#include <QCoreApplication>

#include <exception>

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API Exception:
	public std::exception
{
	Q_DECLARE_TR_FUNCTIONS(cutehmi::base::Exception) // This macro ends with "private:" specifier :o !!!

	public:
		Exception(const QString & what);

		const char * what() const noexcept override;

	private:
		QByteArray m_whatArr;
};

}
}

#endif
