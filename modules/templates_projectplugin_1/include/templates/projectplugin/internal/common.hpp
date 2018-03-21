#ifndef H_MODULES_TEMPLATES__PROJECTPLUGIN__1_INCLUDE_TEMPLATES_PROJECTPLUGIN_INTERNAL_COMMON_HPP    // Edit! Modify include guards.
#define H_MODULES_TEMPLATES__PROJECTPLUGIN__1_INCLUDE_TEMPLATES_PROJECTPLUGIN_INTERNAL_COMMON_HPP    // Edit! Modify include guards.

#include "../metadata.hpp"
#include "../logging.hpp"

#include <cutehmi/MPtr.hpp>

#include <QtGlobal>

#ifdef TEMPLATES_PROJECTPLUGIN_DYNAMIC                      // Edit! Replace 'TEMPLATES_PROJECTPLUGIN' with custom 'VENDOR_MODULE'.
	#ifdef TEMPLATES_PROJECTPLUGIN_BUILD                    // Edit! Replace 'TEMPLATES_PROJECTPLUGIN' with custom 'VENDOR_MODULE'.
        //export symbols to dll
		#define TEMPLATES_PROJECTPLUGIN_API Q_DECL_EXPORT   // Edit! Replace 'TEMPLATES_PROJECTPLUGIN' with custom 'VENDOR_MODULE'.
	#else
		//using functions from dll
		#define TEMPLATES_PROJECTPLUGIN_API Q_DECL_IMPORT   // Edit! Replace 'TEMPLATES_PROJECTPLUGIN' with custom 'VENDOR_MODULE'.
	#endif
#else
	#define TEMPLATES_PROJECTPLUGIN_API                     // Edit! Replace 'TEMPLATES_PROJECTPLUGIN' with custom 'VENDOR_MODULE'.
#endif

#endif
