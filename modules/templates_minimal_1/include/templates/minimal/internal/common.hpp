#ifndef H_MODULES_TEMPLATES__MINIMAL__1_INCLUDE_TEMPLATES_MINIMAL_INTERNAL_COMMON_HPP
#define H_MODULES_TEMPLATES__MINIMAL__1_INCLUDE_TEMPLATES_MINIMAL_INTERNAL_COMMON_HPP

#include "../metadata.hpp"
#include "../logging.hpp"

#include <cutehmi/MPtr.hpp>

#include <QtGlobal>

#ifdef TEMPLATES_MINIMAL_DYNAMIC					// Edit! Replace 'TEMPLATES_MINIMAL' with custom 'VENDOR_MODULE'.
	#ifdef TEMPLATES_MINIMAL_BUILD					// Edit! Replace 'TEMPLATES_MINIMAL' with custom 'VENDOR_MODULE'.
		//export symbols to dll
		#define TEMPLATES_MINIMAL_API Q_DECL_EXPORT	// Edit! Replace 'TEMPLATES_MINIMAL' with custom 'VENDOR_MODULE'.
	#else
		//using functions from dll
		#define TEMPLATES_MINIMAL_API Q_DECL_IMPORT	// Edit! Replace 'TEMPLATES_MINIMAL' with custom 'VENDOR_MODULE'.
	#endif
#else
	#define TEMPLATES_MINIMAL_API					// Edit! Replace 'TEMPLATES_MINIMAL' with custom 'VENDOR_MODULE'.
#endif

#endif
