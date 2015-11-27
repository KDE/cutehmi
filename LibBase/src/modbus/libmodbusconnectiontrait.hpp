#ifndef LIBMODBUSCONNECTIONTRAIT_HPP
#define LIBMODBUSCONNECTIONTRAIT_HPP

#include <modbus.h>

namespace modbus {

template <class DERIVED>
class LibmodbusConnectionTrait
{
	public:
		int readIr(int addr, int num, uint16_t * dest);

		int readR(int addr, int num, uint16_t * dest);

	private:
		const DERIVED & derived() const;

		DERIVED & derived();
};

template <class DERIVED>
int LibmodbusConnectionTrait<DERIVED>::readIr(int addr, int num, uint16_t * dest)
{
	return modbus_read_input_registers(derived().context(), addr, num, dest);
}

template <class DERIVED>
int LibmodbusConnectionTrait<DERIVED>::readR(int addr, int num, uint16_t * dest)
{
	return modbus_read_registers(derived().context(), addr, num, dest);
}

template <class DERIVED>
const DERIVED & LibmodbusConnectionTrait<DERIVED>::derived() const
{
	return static_cast<const DERIVED & >(*this);
}

template <class DERIVED>
DERIVED & LibmodbusConnectionTrait<DERIVED>::derived()
{
	return static_cast<DERIVED & >(*this);
}

}

#endif // LIBMODBUSCONNECTIONTRAIT_HPP

