#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INIT_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INIT_HPP

#include "internal/common.hpp"

#include <cutehmi/Initializer.hpp>

namespace cutehmi {
namespace dataacquisition {

/**
 * %Init. This class performs initialization of data acquisition extension.
 *
 * Normally it is not advisable to create custom instances of this class as extension provides an instance on its own. This can be
 * invalidated particulary by static builds in which case a global variable may not get into resulting binary.
 */
class CUTEHMI_DATAACQUISITION_API Init final:
	public Initializer<Init>
{
	public:
		Init();
};

}
}

#endif
