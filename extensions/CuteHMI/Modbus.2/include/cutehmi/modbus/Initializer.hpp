#ifndef INCLUDECUTEHMIMODBUSINITIALIZER_HPP
#define INCLUDECUTEHMIMODBUSINITIALIZER_HPP

#include "internal/common.hpp"

#include <cutehmi/ExtensionInitializer.hpp>

namespace cutehmi {
namespace modbus {

/**
 * Extension initializer. This class performs initialization of CuteHMI.Modbus extension.
 *
 * Normally it is not advisable to create custom instances of this class as extension provides an instance on its own. This can be
 * invalidated particulary by static builds in which case a global variable may not get into resulting binary.
 *
 * Types registered as meta types:
 *	- AbstractDevice::State
 *  .
 *
 * Classes registered as meta types can be used in string-based, queued signal-slot connections and various functions that rely on
 * QMetaType features.
 */
class CUTEHMI_MODBUS_API Initializer final:
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
