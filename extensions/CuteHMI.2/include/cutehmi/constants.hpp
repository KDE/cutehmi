#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <QtGlobal>

namespace cutehmi {

/**
 * %CuteHMI epsilon. This constant is used in fuzzy comparison functions.
 *
 * @internal Machine epsilon * 0.5 is smallest possible epsilon for which approximation functions make sense.
 */
constexpr qreal EPS = std::numeric_limits<qreal>::epsilon() * 0.5 * 0x10000;	// eps * 0.5 * 2^16.

}

#endif // CONSTANTS_HPP
