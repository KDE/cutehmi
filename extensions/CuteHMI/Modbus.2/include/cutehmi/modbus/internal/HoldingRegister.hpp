#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_HOLDINGREGISTER_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_HOLDINGREGISTER_HPP

#include "../HoldingRegister.hpp"

#include <QAtomicInteger>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * Internal holding register. This is internal class that exposes protected functions such as setValue().
 */
class CUTEHMI_MODBUS_API HoldingRegister:
	public ::cutehmi::modbus::HoldingRegister
{
		typedef ::cutehmi::modbus::HoldingRegister Parent;

	public:
		/**
		 * Constructor.
		 * @param value initial value.
		 */
		explicit HoldingRegister(quint16 value = 0);

		using Parent::setValue;
};

}
}
}

#endif
