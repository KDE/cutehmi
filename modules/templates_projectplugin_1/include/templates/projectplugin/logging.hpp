#ifndef H_MODULES_TEMPLATES__PROJECTPLUGIN__1_INCLUDE_TEMPLATES_PROJECTPLUGIN_LOGGING_HPP    // Edit! Modify include guards.
#define H_MODULES_TEMPLATES__PROJECTPLUGIN__1_INCLUDE_TEMPLATES_PROJECTPLUGIN_LOGGING_HPP    // Edit! Modify include guards.

#include <cutehmi/loggingMacros.hpp>

Q_DECLARE_LOGGING_CATEGORY(templates_projectplugin_1_loggingCategory)    // Edit! Replace 'templates_projectplugin' with custom 'vendor_module'.

namespace templates {        // Edit! Replace 'templates' with custom vendor id.
namespace projectplugin {    // Edit! Replace 'projectplugin' with custom module id.

inline
const QLoggingCategory & loggingCategory()
{
    return templates_projectplugin_1_loggingCategory();    // Edit! Replace 'templates_projectplugin' with custom 'vendor_module'.
}

}
}

#endif
