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
