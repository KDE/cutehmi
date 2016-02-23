#ifndef CUTEHMI_LIBWIDGETS_SRC_PLATFORM_HPP
#define CUTEHMI_LIBWIDGETS_SRC_PLATFORM_HPP

#include <QtGlobal>

#ifdef CUTEHMI_WIDGETS_DYNAMIC
	#ifdef CUTEHMI_WIDGETS_BUILD
		//export symbols to dll
		#define CUTEHMI_WIDGETS_API Q_DECL_EXPORT
	#else
		//using functions from dll
		#define CUTEHMI_WIDGETS_API Q_DECL_IMPORT
	#endif
#else
	#define CUTEHMI_WIDGETS_API
#endif

#endif
