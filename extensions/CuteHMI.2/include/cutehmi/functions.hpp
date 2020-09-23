#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_FUNCTIONS_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_FUNCTIONS_HPP

#include "constants.hpp"

#include <cmath>

namespace cutehmi {

/**
 * Approximately equal. Compares real numbers @a r1, @a r2.
 * @param r1 first number to compare.
 * @param r2 second number to compare.
 * @param eps epsilon tolerance parameter used in comparison.
 * @return @p true when @a r1 and @a r2 are approximately equal, @p false otherwise.
 *
 * @see ale().
 *
 * @internal Donald E. Knuth "Art of Computer Programming" [P 4.2.2 Vol2].
 */
inline
bool ape(qreal r1, qreal r2, qreal eps = EPS)
{
	int exp1, exp2;
	std::frexp(r1, & exp1);
	std::frexp(r2, & exp2);

	// For some reason <= is used in the book to compare both sides. There may be a reason for this, so I'll leave it for now, but
	// the consequence is that image of a function is a bit weird, e.g.:
	// ape(1.0, 1.99, 0.25) -> false, ape(1.0, 2.0, 0.25) -> true, ape(1.0, 2.01, 0.25) -> false
	return std::abs(r2 - r1) <= std::ldexp(eps, std::max(exp1, exp2));
}

/**
 * Almost equal. Compares real numbers @a r1, @a r2. Function similar to ape(), however ale() is slightly stronger than ape() (@a r1
 * and @a r2 must be slightly closer to each other to manifest equality). This function can be problematic, when one of the values
 * is exactly zero, because in such case it returns @p true only if second argument is also exactly zero.
 * @param r1 first number to compare.
 * @param r2 second number to compare.
 * @param eps epsilon tolerance parameter used in comparison.
 * @return @p true when @a r1 and @a r2 are almost equal, @p false otherwise.
 *
 * @see ape().
 *
 * @internal Donald E. Knuth "Art of Computer Programming" [P 4.2.2 Vol2].
 */
inline
bool ale(qreal r1, qreal r2, qreal eps = EPS)
{
	int exp1, exp2;
	std::frexp(r1, & exp1);
	std::frexp(r2, & exp2);

	return std::abs(r2 - r1) <= std::ldexp(eps, std::min(exp1, exp2));
}

/**
 * Considerably less than.
 * @param r1 first number to compare.
 * @param r2 second number to compare.
 * @param eps epsilon tolerance parameter used in comparison.
 * @return @p true when @a r1 is considerably less than @a r2, @p false otherwise.
 *
 * @internal Donald E. Knuth "Art of Computer Programming" [P 4.2.2 Vol2].
 */
inline
bool clt(qreal r1, qreal r2, qreal eps = EPS)
{
	int exp1, exp2;
	std::frexp(r1, & exp1);
	std::frexp(r2, & exp2);

	return r2 - r1 > std::ldexp(eps, std::max(exp1, exp2));
}

/**
 * Considerably greater than.
 * @param r1 first number to compare.
 * @param r2 second number to compare.
 * @param eps epsilon tolerance parameter used in comparison.
 * @return @p true when @a r1 is considerably greater than @a r2, @p false otherwise.
 *
 * @internal Donald E. Knuth "Art of Computer Programming" [P 4.2.2 Vol2].
 */
inline
bool cgt(qreal r1, qreal r2, qreal eps = EPS)
{
	int exp1, exp2;
	std::frexp(r1, & exp1);
	std::frexp(r2, & exp2);

	return r1 - r2 > std::ldexp(eps, std::max(exp1, exp2));
}

}

#endif

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
