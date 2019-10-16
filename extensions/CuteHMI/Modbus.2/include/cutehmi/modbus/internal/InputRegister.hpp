#ifndef INCLUDECUTEHMIMODBUSINTERNALINPUTREGISTER_HPP
#define INCLUDECUTEHMIMODBUSINTERNALINPUTREGISTER_HPP

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

#endif // INCLUDECUTEHMIMODBUSINTERNALREGISTER16_HPP
