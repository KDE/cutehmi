#ifndef CUTEHMI_LIBBASE_SRC_PLATFORM_HPP
#define CUTEHMI_LIBBASE_SRC_PLATFORM_HPP

#include <QtGlobal>

#ifdef CUTEHMI_DYNAMIC
	#ifdef CUTEHMI_BUILD
		//export symbols to dll
		#define CUTEHMI_API Q_DECL_EXPORT
	#else
		//using functions from dll
		#define CUTEHMI_API Q_DECL_IMPORT
	#endif
#else
	#define CUTEHMI_API
#endif

#endif
