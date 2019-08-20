#ifndef INCLUDECUTEHMISERVICESINITIALIZER_HPP
#define INCLUDECUTEHMISERVICESINITIALIZER_HPP

#include "internal/common.hpp"

#include <cutehmi/ExtensionInitializer.hpp>

namespace cutehmi {
namespace services {

/**
 * Extension initializer. This class performs initialization of CuteHMI.Services extension.
 *
 * Normally it is not advisable to create custom instances of this class as extension provides an instance on its own. This can be
 * invalidated particulary by static builds in which case a global variable may not get into resulting binary.
 *
 * Types registered as meta types:
 *	- Serviceable *
 *  .
 *
 * Classes registered as meta types can be used in string-based, queued signal-slot connections and various functions that rely on
 * QMetaType features.
 */
class CUTEHMI_SERVICES_API Initializer final:
	public ExtensionInitializer<Initializer>
{
	public:
		/**
		 * Default constructor.
		 */
		Initializer();
};

}
}

#endif // INCLUDECUTEHMIMODBUSINITIALIZER_HPP
