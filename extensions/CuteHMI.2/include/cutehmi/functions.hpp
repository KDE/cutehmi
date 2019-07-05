#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "constants.hpp"

namespace cutehmi {

/**
 * Epsilon for a number. Get epsilon for real number @a r, that means smallest number which added to @a r changes value of @a r.
 * @param r real number.
 * @return smallest number, which added to @a r changes value of @a r. If @a r is positive number, then returned number is also
 * positive. Otherwise negative number is returned.
 *
 * @see absEps().
 */
inline
qreal eps(qreal r)
{
	static constexpr qreal MACHINE_EPS = std::numeric_limits<qreal>::epsilon() * 0.5;

	int exp;
	std::frexp(r, & exp);
	return std::ldexp(std::signbit(r) ? -MACHINE_EPS : MACHINE_EPS, exp);
}

/**
 * Absolute epsilon for a number. Works in similar way to eps() function, except that absolute value is returned instead of signed
 * one.
 * @param r real number.
 * @return smallest number which added to @a r changes value of @a r. Always non-negative value is returned.
 *
 * @see eps().
 */
inline
qreal absEps(qreal r)
{
	static constexpr qreal MACHINE_EPS = std::numeric_limits<qreal>::epsilon() * 0.5;

	int exp;
	std::frexp(r, & exp);
	return std::ldexp(MACHINE_EPS, exp);
}

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

#endif // FUNCTIONS_HPP
