#ifndef H_MODULES_TEMPLATES__XMLBACKEND__1_INCLUDE_TEMPLATES_XMLBACKEND_LOGGING_HPP	// Edit! Modify include guards.
#define H_MODULES_TEMPLATES__XMLBACKEND__1_INCLUDE_TEMPLATES_XMLBACKEND_LOGGING_HPP	// Edit! Modify include guards.

#include <cutehmi/loggingMacros.hpp>

Q_DECLARE_LOGGING_CATEGORY(templates_xmlbackend_1_loggingCategory)	// Edit! Replace 'templates_xmlbackend' with custom 'vendor_module'.

namespace templates {	// Edit! Replace 'templates' with custom vendor id.
namespace xmlbackend {		// Edit! Replace 'xmlbackend' with custom module id.

inline
const QLoggingCategory & loggingCategory()
{
	return templates_xmlbackend_1_loggingCategory();	// Edit! Replace 'templates_xmlbackend' with custom 'vendor_module'.
}

}
}

#endif
