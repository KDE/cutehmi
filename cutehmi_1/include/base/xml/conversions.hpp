#ifndef CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_XML_CONVERSIONS_HPP
#define CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_XML_CONVERSIONS_HPP

#include "../internal/common.hpp"

#include <QString>

namespace cutehmi {
namespace base {
namespace xml {

/**
 * @brief Minimal port number of a random port. By default a number defined by
 * IANA for a dynamic port range is used (http://www.rfc-editor.org/rfc/rfc6335.txt).
 */
CUTEHMI_BASE_API extern uint randomPortBegin;

CUTEHMI_BASE_API extern uint randomPortEnd;

#ifndef CUTEHMI_BASE_XML_RANDOM_PORT_BEGIN
	#define CUTEHMI_BASE_XML_RANDOM_PORT_BEGIN 49152 // Minimal port number of a random port. By default a number defined by IANA for a dynamic port range is used (http://www.rfc-editor.org/rfc/rfc6335.txt).
#endif

#ifndef CUTEHMI_BASE_XML_RANDOM_PORT_END
	#define CUTEHMI_BASE_XML_RANDOM_PORT_END 65535 // Maximal port number of a random port.
#endif

/**
 * Convert string to a port number. Extends standard QString::toUint() function by the
 * ability of picking random port number in a deterministic fashion. If @a string contains
 * pattern 'randPlus([0-9]*)', then randomly selected port number will be used. Number
 * '[0-9]*' indicates a number that should be added to the randomly selected port.
 * @param string string to convert.
 * @param ok set to @p true when conversion was succesful, otherwise set to @p false.
 * @return port number.
 */
CUTEHMI_BASE_API uint portFromString(const QString & string, bool & ok);

CUTEHMI_BASE_API QString portToString(uint port, bool random);

}
}
}

#endif // STRING_HPP
