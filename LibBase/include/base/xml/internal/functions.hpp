#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_XML_INTERNAL_FUNCTIONS_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_XML_INTERNAL_FUNCTIONS_HPP

#include "../../internal/common.hpp"

#include <QXmlStreamReader>

namespace cutehmi {
namespace base {
namespace xml {
namespace internal {

QString CUTEHMI_BASE_API readerPositionString(const QXmlStreamReader & xmlReader);

}
}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
