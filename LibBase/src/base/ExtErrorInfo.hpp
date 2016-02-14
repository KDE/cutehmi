#ifndef EXTERRORINFO_HPP
#define EXTERRORINFO_HPP

#include "ErrorInfo.hpp"
#include "ExtError.hpp"

namespace cutehmi {
namespace base {

struct ExtErrorInfo:
	public ErrorInfo
{
	QString details;			///< Error details.
};

/**
 * Get extended error info. Produces ExtErrorInfo from instance of ExtError or its subclass.
 * @param err instance of ExtError class or its subclass.
 * @return extended error info structure.
 */
template <typename EXTERR>
ExtErrorInfo extErrorInfo(EXTERR err)
{
	return ExtErrorInfo{err.code(), typeid(EXTERR).name(), err.str(), err.details()};
}

}
}

#endif // EXTERRORINFO_HPP

