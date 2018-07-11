#ifndef H_MODULES_TEMPLATES__MINIMAL__1_INCLUDE_TEMPLATES_MINIMAL_LOGGING_HPP
#define H_MODULES_TEMPLATES__MINIMAL__1_INCLUDE_TEMPLATES_MINIMAL_LOGGING_HPP

#include <cutehmi/loggingMacros.hpp>

Q_DECLARE_LOGGING_CATEGORY(templates_minimal_1_loggingCategory)	// Edit! Replace 'templates_minimal' with custom 'vendor_module'.

namespace templates {	// Edit! Replace 'templates' with custom vendor id.
namespace minimal {		// Edit! Replace 'minimal' with custom module id.

inline
const QLoggingCategory & loggingCategory()
{
	return templates_minimal_1_loggingCategory();	// Edit! Replace 'templates_minimal' with custom 'vendor_module'.
}

}
}

#endif
