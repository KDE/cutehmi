#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_INPUTREGISTER_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_INPUTREGISTER_HPP

#include "../InputRegister.hpp"

#include <QAtomicInteger>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * Internal input register. This is internal class that exposes protected functions such as setValue().
 */
class CUTEHMI_MODBUS_API InputRegister:
	public ::cutehmi::modbus::InputRegister
{
		typedef ::cutehmi::modbus::InputRegister Parent;

	public:
		/**
		 * Constructor.
		 * @param value initial value.
		 */
		explicit InputRegister(quint16 value = 0);

		using Parent::setValue;
};

}
}
}

#endif
