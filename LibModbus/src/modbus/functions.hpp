#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_FUNCTIONS_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_FUNCTIONS_HPP

#include "../platform.hpp"

#include <modbus.h>

#include <QtEndian>

namespace cutehmi {
namespace modbus {

template <typename T>
T toBigEndian(T src)
{
	// Will use Qt endian functions, but need to assert that uchar is 8 bit wide. Qt implementation seems to be unaware that
	// sizeof(char) == 1 byte == not necessarily 8 bits.
	static_assert(std::numeric_limits<uchar>::digits == 8, "uchar must be 8 bit wide");

	return qToBigEndian(src);
}

template <typename T>
T fromBigEndian(T src)
{
	// Will use Qt endian functions, but need to assert that uchar is 8 bit wide. Qt implementation seems to be unaware that
	// sizeof(char) == 1 byte == not necessarily 8 bits.
	static_assert(std::numeric_limits<uchar>::digits == 8, "uchar must be 8 bit wide");

	return qFromBigEndian(src);
}

template <typename T>
T toLittleEndian(T src)
{
	// Will use Qt endian functions, but need to assert that uchar is 8 bit wide. Qt implementation seems to be unaware that
	// sizeof(char) == 1 byte == not necessarily 8 bits.
	static_assert(std::numeric_limits<uchar>::digits == 8, "uchar must be 8 bit wide");

	return qToLittleEndian(src);
}

template <typename T>
T fromLittleEndian(T src)
{
	// Will use Qt endian functions, but need to assert that uchar is 8 bit wide. Qt implementation seems to be unaware that
	// sizeof(char) == 1 byte == not necessarily 8 bits.
	static_assert(std::numeric_limits<uchar>::digits == 8, "uchar must be 8 bit wide");

	return qFromLittleEndian(src);
}

/**
 * Store int as 16 bit unsigned integer.
 * @param value value to be stored.
 * @return
 *
 * @warning it is assumed that value uses 2's complement convention.
 */
CUTEHMI_MODBUS_API uint16_t intToUint16(int value);

/**
 * Restore int from 16 bit unsigned integer.
 * @param value value to be restored.
 * @return
 *
 * @warning it is assumed that value uses 2's complement convention.
 */
CUTEHMI_MODBUS_API int intFromUint16(uint16_t value);

}
}

#endif

