#ifndef CUTEHMI_LIBBASE_SRC_PLATFORM_HPP
#define CUTEHMI_LIBBASE_SRC_PLATFORM_HPP

#include <QtGlobal>

#ifdef CUTEHMI_BASE_DYNAMIC
	#ifdef CUTEHMI_BASE_BUILD
		//export symbols to dll
		#define CUTEHMI_BASE_API Q_DECL_EXPORT
	#else
		//using functions from dll
		#define CUTEHMI_BASE_API Q_DECL_IMPORT
	#endif
#else
	#define CUTEHMI_BASE_API
#endif

#endif
