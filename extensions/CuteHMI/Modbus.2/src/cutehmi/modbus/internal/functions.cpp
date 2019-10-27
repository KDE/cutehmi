#include <cutehmi/modbus/internal/functions.hpp>

#include <QtGlobal>

#include <limits>

namespace cutehmi {
namespace modbus {
namespace internal {

quint16 intToUint16(int value)
{
	// Note: int is guranteed to be at least 16 bits wide by a standard.

	// Check if value can be stored in 16 bits.
	Q_ASSERT_X(value <= std::numeric_limits<qint16>::max(), __func__, "value is below a limit of 16 bit storage");
	Q_ASSERT_X(value >= std::numeric_limits<qint16>::min(), __func__, "value is over a limit of 16 bit storage");

	return int16ToUint16(static_cast<qint16>(value));
}

quint16 int16ToUint16(qint16 value)
{
	// A bit paranoic, but int can be either one's or two's complement (http://en.cppreference.com/w/cpp/language/types).
	// Since one's complement machines are probably non-existent, just assert that machine is two's complement.
	// On one's complement machines ~0 == -0, on two's complement machines ~0 == -1.
	Q_ASSERT_X(-1 == ~0, __func__, "only two's complement machines are supported by this function");

	// Conversion from signed to unsigned type is well defined by a standard.
	// "If the destination type is unsigned, the resulting value is the smallest unsigned value equal to the source value modulo 2^n
	//  where n is the number of bits used to represent the destination type. That is, depending on whether the destination type is
	//  wider or narrower, signed integers are sign-extended[footnote 1] or truncated and unsigned integers are zero-extended or
	//  truncated respectively." -- http://en.cppreference.com/w/cpp/language/implicit_cast

	return static_cast<quint16>(value);
}

qint16 int16FromUint16(quint16 value)
{
	// A bit paranoic, but int can be either one's or two's complement (http://en.cppreference.com/w/cpp/language/types).
	// Since one's complement machines are probably non-existent, just assert that machine is two's complement.
	// On one's complement machines ~0 == -0, on two's complement machines ~0 == -1.
	Q_ASSERT_X(-1 == ~0, __func__, "only two's complement machines are supported by this function");

	// Conversion from unsigned to signed type is well-defined if value can be represented in destination int.
	// "If the destination type is signed, the value does not change if the source integer can be represented in the destination type.
	//  Otherwise the result is implementation-defined. (Note that this is different from signed integer arithmetic overflow, which
	//  is undefined)." -- http://en.cppreference.com/w/cpp/language/implicit_cast
	// Anyways, we need to make reverse of int16ToUint16(), not represent value directly.

	if (value > std::numeric_limits<qint16>::max())
		return -static_cast<qint16>(std::numeric_limits<quint16>::max() - value) - 1;
	else
		return static_cast<qint16>(value);
}

}
}
}

//(c)C: Copyright © 2019, Michal Policht <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
