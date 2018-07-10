#ifndef H_MODULES_CUTEHMI__MODBUS__1_INCLUDE_CUTEHMI_MODBUS_INTERNAL_FUNCTIONS_HPP
#define H_MODULES_CUTEHMI__MODBUS__1_INCLUDE_CUTEHMI_MODBUS_INTERNAL_FUNCTIONS_HPP

#include "common.hpp"

#include <modbus/modbus.h>

#include <QtEndian>

namespace cutehmi {
namespace modbus {
namespace internal {

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
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
