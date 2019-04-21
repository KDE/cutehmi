#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_INITIALIZER_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_INITIALIZER_HPP

#include "ExtensionInitializer.hpp"

namespace cutehmi {

/**
 * Extension initializer. This class performs initialization of CuteHMI extension.
 *
 * Normally it is not advisable to create custom instances of this class as extension provides an instance on its own. This can be
 * invalidated particulary by static builds in which case a global variable may not get into resulting binary.
 *
 * Classes registered as meta types:
 *	- ErrorInfo
 *  .
 *
 * Classes registered as meta types can be used in string-based, queued signal-slot connections and various functions that rely on
 * QMetaType features.
 */
class CUTEHMI_API Initializer final:
	public ExtensionInitializer<Initializer>
{
	public:
		/**
		 * Default constructor.
		 */
		Initializer();
};

}

#endif
