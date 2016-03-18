#ifndef CUTEHMI_LIBBASE_SRC_BASE_EXTERRORINFO_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_EXTERRORINFO_HPP

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

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
