#ifndef INCLUDECUTEHMIMODBUSINTERNALCOIL_HPP
#define INCLUDECUTEHMIMODBUSINTERNALCOIL_HPP

#include "../Coil.hpp"

#include <QAtomicInteger>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * Internal coil. This is internal class that exposes protected functions such as setValue().
 */
class CUTEHMI_MODBUS_API Coil:
	public ::cutehmi::modbus::Coil
{
		typedef ::cutehmi::modbus::Coil Parent;

	public:
		/**
		 * Constructor.
		 * @param value initial value.
		 */
		explicit Coil(bool value = false);

		using Parent::setValue;
};

}
}
}

#endif // INCLUDECUTEHMIMODBUSINTERNALREGISTER16_HPP
