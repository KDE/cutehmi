#ifndef H_EXTENSIONS_CUTEHMI_TEST_0_INCLUDE_CUTEHMI_TEST_TESTS_HPP
#define H_EXTENSIONS_CUTEHMI_TEST_0_INCLUDE_CUTEHMI_TEST_TESTS_HPP

#include "random.hpp"

#include <QtTest/QtTest>

#include <functional>
#include <algorithm>

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
template <class CM, typename T, class C, typename std::enable_if<IsIntType<T>::value || std::is_floating_point<T>::value, bool>::type = true>
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
 * Test accessors. Overloaded function for accessors that operate on Boolean types.
 *
 * @tparam CM name of a class containing member access functions.
 * @tparam C object class (this should be the same as @a CM). This template
 * parameter is introduced to prevent deduction of conflicting types for
 * function parameters.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param p propbablity of generating @p true.
 */
template <class CM, class C>
void testAccessors(bool (CM::* getter)() const, void (CM::* setter)(bool), C && object, double p = 0.5)
{
	bool value = cutehmi::test::rand<bool>(p);
	(object.*setter)(value);
	QCOMPARE((object.*getter)(), value);
}

//<CuteHMI.Test-1.workaround target="MSVC" cause="bug">
// MSVC has problems parsing function declarations with function pointers and default arguments initialized with braces.
// Workaround is to use overloaded function instead of default argument.

/**
 * Test accessors. Overloaded function for accessors that operate on QString.
 *
 * @tparam CM name of a class containing member access functions.
 * @tparam C object class (this should be the same as @a CM). This template
 * parameter is introduced to prevent deduction of conflicting types for
 * function parameters.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param length string length.
 * @param categories character categories of which string should be composed from.
 *
 * @note This overloaded function is provided as CuteHMI.Test-1.workaround. It uses
 * {QChar::Letter_Uppercase, QChar::Letter_Lowercase, QChar::Number_DecimalDigit} as character categories.
 */
template <class CM, class C>
void testAccessors(QString (CM::* getter)() const, void (CM::* setter)(const QString &), C && object, int length, const QList<QChar::Category> & categories)
{
	QString str = cutehmi::test::rand<QString>(length, categories);
	(object.*setter)(str);
	QCOMPARE((object.*getter)(), str);
}


/**
 * Test accessors. Overloaded function for accessors that operate on QString.
 *
 * @tparam CM name of a class containing member access functions.
 * @tparam C object class (this should be the same as @a CM). This template
 * parameter is introduced to prevent deduction of conflicting types for
 * function parameters.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param length string length.
 */
template <class CM, class C>
void testAccessors(QString (CM::* getter)() const, void (CM::* setter)(const QString &), C && object, int length = rand(0, 255))
{
	testAccessors(getter, setter, object, length, {QChar::Letter_Uppercase, QChar::Letter_Lowercase, QChar::Number_DecimalDigit});
}

//</CuteHMI.Test-1.workaround>

//<CuteHMI.Test-1.workaround target="MSVC" cause="bug">
// MSVC has problems parsing function declarations with function pointers and default arguments initialized with braces.
// Workaround is to use overloaded function instead of default argument.

/**
 * Test accessors. Overloaded function for accessors that operate on QStringList.
 *
 * @tparam CM name of a class containing member access functions.
 * @tparam C object class (this should be the same as @a CM). This template
 * parameter is introduced to prevent deduction of conflicting types for
 * function parameters.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param size string list size.
 * @param length strings length.
 * @param categories character categories of which strings should be composed from.
 */
template <class CM, class C>
void testAccessors(QStringList (CM::* getter)() const, void (CM::* setter)(const QStringList &), C && object, int size, int length, const QList<QChar::Category> & categories)
{
	QStringList list = cutehmi::test::rand<QStringList>(size, length, categories);
	(object.*setter)(list);
	QCOMPARE((object.*getter)(), list);
}

/**
 * Test accessors. Overloaded function for accessors that operate on QStringList.
 *
 * @tparam CM name of a class containing member access functions.
 * @tparam C object class (this should be the same as @a CM). This template
 * parameter is introduced to prevent deduction of conflicting types for
 * function parameters.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param size string list size.
 * @param length strings length.
 *
 * @note This overloaded function is provided as CuteHMI.Test-1.workaround. It uses
 * {QChar::Letter_Uppercase, QChar::Letter_Lowercase, QChar::Number_DecimalDigit} as character categories.
 */
template <class CM, class C>
void testAccessors(QStringList (CM::* getter)() const, void (CM::* setter)(const QStringList &), C && object, int size = rand(0, 255), int length = rand(0, 255))
{
	testAccessors(getter, setter, object, size, length, {QChar::Letter_Uppercase, QChar::Letter_Lowercase, QChar::Number_DecimalDigit});
}

//</CuteHMI.Test-1.workaround>

/**
 * Test accessors. This overloaded function uses default constructed object as third argument to
 * testAccessors(T (CM::* getter)() const, void (CM::* setter)(T), C && object, T min, T max).
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

/**
 * Test accessors. This overloaded function uses default constructed object as third argument to
 * testAccessors(T (CM::* getter)() const, void (CM::* setter)(T), C && object, int length, QList<QChar::Category> categories).
 *
 * @tparam CM name of a class containing member access functions.
 * @tparam T type of value to set or get by access functions.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 */
template <class CM, typename T>
void testAccessors(T (CM::*getter)() const, void (CM::*setter)(const T &))
{
	testAccessors(getter, setter, CM());
}

/**
 * Compare two arrays if their corresponding elements are equal.
 * @tparam T type of array elements.
 * @param arr1 first array.
 * @param arr2 second array.
 * @param size size of arrays.
 * @return @p true if each element in the first array is equal to a
 * corresponding element in the second array. Otherwise function returns @p false.
 */
template <typename T>
bool arrEqual(const T * arr1, const T * arr2, std::size_t size)
{
	return std::equal(arr1, arr1 + size, arr2);
}

/**
 * Compare two arrays if their corresponding elements are inequal.
 * @tparam T type of array elements.
 * @param arr1 first array.
 * @param arr2 second array.
 * @param size size of arrays.
 * @return @p true if each element in the first array is different from a
 * corresponding element in the second array. Otherwise function returns @p false.
 */
template <typename T>
bool arrInequal(const T * arr1, const T * arr2, std::size_t size)
{
	for (std::size_t i = 0; i < size; i++)
		if (*(arr1++) == *(arr2++))
			return false;
	return true;
}

/**
 * Check if all array elements are equal to specified value.
 * @tparam T type of array elements.
 * @param arr array to check.
 * @param size array size.
 * @param T val value to compare array elements with.
 * @return @p true if all elements of an array are equal to @a val, @p false
 * otherwise.
 */
template <typename T>
bool arrEqual(const T * arr, T val, std::size_t size)
{
	for (std::size_t i = 0; i < size; i++)
		if (*(arr++) != val)
			return false;
	return true;
}

/**
 * Check if all array elements are different than a specified value.
 * @tparam T type of array elements.
 * @param arr array to check.
 * @param size array size.
 * @param T val value to compare array elements with.
 * @return @p true if all elements of an array are different than @a val,
 * @p false otherwise.
 */
template <typename T>
bool arrInequal(const T * arr, T val, std::size_t size)
{
	for (std::size_t i = 0; i < size; i++)
		if (*(arr++) == val)
			return false;
	return true;
}

}
}

#endif

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
