#ifndef CUTEHMI_LIBMODBUS_SRC_PLATFORM_HPP
#define CUTEHMI_LIBMODBUS_SRC_PLATFORM_HPP

#include <QtGlobal>

#ifdef CUTEHMI_MODBUS_DYNAMIC
	#ifdef CUTEHMI_MODBUS_BUILD
		//export symbols to dll
		#define CUTEHMI_MODBUS_API Q_DECL_EXPORT
	#else
		//using functions from dll
		#define CUTEHMI_MODBUS_API Q_DECL_IMPORT
	#endif
#else
	#define CUTEHMI_MODBUS_API
#endif

#endif
