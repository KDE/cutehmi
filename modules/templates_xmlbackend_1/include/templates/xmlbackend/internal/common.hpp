#ifndef H_MODULES_TEMPLATES__XMLBACKEND__1_INCLUDE_TEMPLATES_XMLBACKEND_INTERNAL_COMMON_HPP	// Edit! Modify include guards.
#define H_MODULES_TEMPLATES__XMLBACKEND__1_INCLUDE_TEMPLATES_XMLBACKEND_INTERNAL_COMMON_HPP	// Edit! Modify include guards.

#include "../metadata.hpp"
#include "../logging.hpp"

#include <cutehmi/MPtr.hpp>

#include <QtGlobal>

#ifdef TEMPLATES_XMLBACKEND_DYNAMIC					// Edit! Replace 'TEMPLATES_XMLBACKEND' with custom 'VENDOR_MODULE'.
	#ifdef TEMPLATES_XMLBACKEND_BUILD					// Edit! Replace 'TEMPLATES_XMLBACKEND' with custom 'VENDOR_MODULE'.
		//export symbols to dll
		#define TEMPLATES_XMLBACKEND_API Q_DECL_EXPORT	// Edit! Replace 'TEMPLATES_XMLBACKEND' with custom 'VENDOR_MODULE'.
	#else
		//using functions from dll
		#define TEMPLATES_XMLBACKEND_API Q_DECL_IMPORT	// Edit! Replace 'TEMPLATES_XMLBACKEND' with custom 'VENDOR_MODULE'.
	#endif
#else
	#define TEMPLATES_XMLBACKEND_API					// Edit! Replace 'TEMPLATES_XMLBACKEND' with custom 'VENDOR_MODULE'.
#endif

#endif
