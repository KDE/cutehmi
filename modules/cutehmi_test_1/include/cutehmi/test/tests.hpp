#ifndef H_MODULES_CUTEHMI__TEST__1_INCLUDE_CUTEHMI_TESTS_HPP
#define H_MODULES_CUTEHMI__TEST__1_INCLUDE_CUTEHMI_TESTS_HPP

#include "random.hpp"

#include <QtTest/QtTest>

#include <functional>

namespace cutehmi {
namespace test {

/**
 * Test accessors. Convenient function to test "getter" and "setter" functions.
 * Functions are tested with @a min, @a max and random value in between.
 *
 * @tparam CM name of a class containing member access functions.
 * @tparam T type of value to set or get by access functions.
 * @tparam C object class (this should be the same as @a CM). This template
 * parameter is introduced to prevent deduction of conflicting types for
 * function parameters.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param min minimal value that can be set by "setter" function.
 * @param max maximal value that can be set by "setter" function.
 */
template <class CM, typename T, class C>
void testAccessors(T (CM::* getter)() const, void (CM::* setter)(T), C && object, T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
{
	(object.*setter)(min);
	QCOMPARE((object.*getter)(), min);

	(object.*setter)(max);
	QCOMPARE((object.*getter)(), max);

	T value = cutehmi::test::rand<T>(min, max);
	(object.*setter)(value);
	QCOMPARE((object.*getter)(), value);
}

/**
 * Test accessors. This overloaded function uses default constructed object as
 * third argument to
 * testAccessors(T (CM::* getter)() const, void (CM::* setter)(T), C && object, T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()).
 *
 * @tparam CM name of a class containing member access functions.
 * @tparam T type of value to set or get by access functions.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 */
template <class CM, typename T>
void testAccessors(T (CM::*getter)() const, void (CM::*setter)(T))
{
	testAccessors(getter, setter, CM());
}

}
}

#endif
