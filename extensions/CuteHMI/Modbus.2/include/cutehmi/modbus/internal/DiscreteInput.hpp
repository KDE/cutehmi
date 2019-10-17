#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DISCRETEINPUT_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_DISCRETEINPUT_HPP

#include "../DiscreteInput.hpp"

#include <QAtomicInteger>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * Internal discrete input. This is internal class that exposes protected functions such as setValue().
 */
class CUTEHMI_MODBUS_API DiscreteInput:
	public ::cutehmi::modbus::DiscreteInput
{
		typedef ::cutehmi::modbus::DiscreteInput Parent;

	public:
		/**
		 * Constructor.
		 * @param value initial value.
		 */
		explicit DiscreteInput(bool value = 0);

		using Parent::setValue;
};

}
}
}

#endif
