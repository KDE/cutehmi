#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_4_INCLUDE_CUTEHMI_MODBUS_INTERNAL_FUNCTIONS_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_4_INCLUDE_CUTEHMI_MODBUS_INTERNAL_FUNCTIONS_HPP

#include "common.hpp"

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
 * Store integer as 16 bit unsigned integer. This is convenient function that casts @p int to 16 bit integer and then stores it as
 * 16 bit unsigned integer.
 * @param value value to be stored. Must be within 16 bit interger range (@p int is guaranteed to be at least 16 bits wide by the
 * standard).
 * @return value converted to 16 bit unsigned integer.
 *
 * @remark It is assumed that @a value uses two's complement convention (one's complement machines are probably non-existent).
 */
quint16 CUTEHMI_MODBUS_PRIVATE intToUint16(int value);

/**
 * Store 16 bit integer as 16 bit unsigned integer.
 * @param value value to be stored.
 * @return value converted to 16 bit unsigned integer.
 *
 * @remark It is assumed that @a value uses two's complement convention (one's complement machines are probably non-existent).
 */
quint16 CUTEHMI_MODBUS_PRIVATE int16ToUint16(qint16 value);

/**
 * Restore 16 bit integer from 16 bit unsigned integer.
 * @param value value to be restored.
 * @return value converted to 16 bit integer.
 *
 * @remark It is assumed that @a value uses two's complement convention (one's complement machines are probably non-existent).
 */
qint16 CUTEHMI_MODBUS_PRIVATE int16FromUint16(quint16 value);

}
}
}

#endif

//(c)C: Copyright © 2021, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
