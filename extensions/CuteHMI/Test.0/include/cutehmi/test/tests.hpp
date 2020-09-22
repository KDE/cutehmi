#ifndef H_EXTENSIONS_CUTEHMI_TEST_0_INCLUDE_CUTEHMI_TEST_TESTS_HPP
#define H_EXTENSIONS_CUTEHMI_TEST_0_INCLUDE_CUTEHMI_TEST_TESTS_HPP

#include "random.hpp"

#include <cutehmi/wrappers.hpp>

#include <QtTest/QtTest>

#include <functional>
#include <algorithm>

namespace cutehmi {
namespace test {

/**
 * Test accessors. Convenient function to test "getter" and "setter" functions. Functions are tested with @a min, @a max and some
 * random value in between.
 *
 * @tparam C name of a class containing member access functions.
 * @tparam T type of value to set or get by access functions.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param min minimal value that can be set by "setter" function.
 * @param max maximal value that can be set by "setter" function.
 */
template <class C, typename T, typename std::enable_if<IsIntType<T>::value, bool>::type = true>
void testAccessors(T (C::* getter)() const, void (C::* setter)(T), C & object, T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max())
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
 * Test accessors. Convenient function to test "getter" and "setter" functions. Functions are tested with @a min, @a max and some
 * random value in between. Performs tests on default constructed object.
 *
 * @tparam C name of a class containing member access functions.
 * @tparam T type of value to set or get by access functions.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param min minimal value that can be set by "setter" function.
 * @param max maximal value that can be set by "setter" function.
 */
template <class C, typename T, typename std::enable_if<IsIntType<T>::value, bool>::type = true>
void testAccessors(T (C::* getter)() const, void (C::* setter)(T), T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max())
{
	C object;
	testAccessors(getter, setter, object, min, max);
}

/**
 * Test accessors. Convenient function to test "getter" and "setter" functions. Functions are tested with @a min, @a max and some
 * random value in between.
 *
 * @tparam C name of a class containing member access functions.
 * @tparam T type of value to set or get by access functions.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param min minimal value that can be set by "setter" function.
 * @param max maximal value that can be set by "setter" function.
 */
template <class C, typename T, typename std::enable_if<std::is_floating_point<T>::value, bool>::type = true>
void testAccessors(T (C::* getter)() const, void (C::* setter)(T), C & object, T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max())
{
	(object.*setter)(min);
	QCOMPARE((object.*getter)(), min);

	(object.*setter)(max);
	QCOMPARE((object.*getter)(), max);

	T value = cutehmi::test::randPick<T>(min, max);
	(object.*setter)(value);
	QCOMPARE((object.*getter)(), value);
}

/**
 * Test accessors. Convenient function to test "getter" and "setter" functions. Functions are tested with @a min, @a max and some
 * random value in between. Performs tests on default constructed object.
 *
 * @tparam C name of a class containing member access functions.
 * @tparam T type of value to set or get by access functions.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param min minimal value that can be set by "setter" function.
 * @param max maximal value that can be set by "setter" function.
 */
template <class C, typename T, typename std::enable_if<std::is_floating_point<T>::value, bool>::type = true>
void testAccessors(T (C::* getter)() const, void (C::* setter)(T), T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max())
{
	C object;
	testAccessors(getter, setter, object, min, max);
}

/**
 * Test accessors. Overloaded function for accessors that operate on Boolean types.
 *
 * @tparam C name of a class containing member access functions.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 */
template <class C>
void testAccessors(bool (C::* getter)() const, void (C::* setter)(bool), C & object)
{
	(object.*setter)(true);
	QCOMPARE((object.*getter)(), true);

	(object.*setter)(false);
	QCOMPARE((object.*getter)(), false);
}

/**
 * Test accessors. Overloaded function for accessors that operate on Boolean types. Performs test on default constructed object.
 *
 * @tparam C name of a class containing member access functions.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 */
template <class C>
void testAccessors(bool (C::* getter)() const, void (C::* setter)(bool))
{
	C object;
	testAccessors(getter, setter, object);
}

//<CuteHMI.Test-1.workaround target="MSVC" cause="bug">
// MSVC has problems parsing function declarations with function pointers and default arguments initialized with braces.
// Workaround is to use overloaded function instead of default argument.

/**
 * Test accessors. Overloaded function for accessors that operate on QString.
 *
 * @tparam C name of a class containing member access functions.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param length string length.
 * @param categories character categories of which string should be composed from.
 */
template <class C>
void testAccessors(QString (C::* getter)() const, void (C::* setter)(const QString &), C & object, int length, const QList<QChar::Category> & categories)
{
	QString str = cutehmi::test::rand<QString>(length, categories);
	(object.*setter)(str);
	QCOMPARE((object.*getter)(), str);
}

/**
 * Test accessors. Overloaded function for accessors that operate on QString.
 *
 * @tparam C name of a class containing member access functions.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param length string length.
 *
 * @note This overloaded function is provided as CuteHMI.Test-1.workaround. It uses
 * {QChar::Letter_Uppercase, QChar::Letter_Lowercase, QChar::Number_DecimalDigit} as character categories.
 */
template <class C>
void testAccessors(QString (C::* getter)() const, void (C::* setter)(const QString &), C & object, int length = rand(0, 255))
{
	testAccessors(getter, setter, object, length, {QChar::Letter_Uppercase, QChar::Letter_Lowercase, QChar::Number_DecimalDigit});
}

/**
 * Test accessors. Overloaded function for accessors that operate on QString. Performs test on default constructed object.
 *
 * @tparam C name of a class containing member access functions.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param length string length.
 * @param categories character categories of which string should be composed from.
 */
template <class C>
void testAccessors(QString (C::* getter)() const, void (C::* setter)(const QString &), int length, const QList<QChar::Category> & categories)
{
	C object;
	testAccessors(getter, setter, object, length, categories);
}

/**
 * Test accessors. Overloaded function for accessors that operate on QString. Performs test on default constructed object.
 *
 * @tparam C name of a class containing member access functions.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param length string length.
 *
 * @note This overloaded function is provided as CuteHMI.Test-1.workaround. It uses
 * {QChar::Letter_Uppercase, QChar::Letter_Lowercase, QChar::Number_DecimalDigit} as character categories.
 */
template <class C>
void testAccessors(QString (C::* getter)() const, void (C::* setter)(const QString &), int length = rand(0, 255))
{
	C object;
	testAccessors(getter, setter, object, length);
}

//</CuteHMI.Test-1.workaround>

//<CuteHMI.Test-1.workaround target="MSVC" cause="bug">
// MSVC has problems parsing function declarations with function pointers and default arguments initialized with braces.
// Workaround is to use overloaded function instead of default argument.

/**
 * Test accessors. Overloaded function for accessors that operate on QStringList.
 *
 * @tparam C name of a class containing member access functions.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param size string list size.
 * @param length strings length.
 * @param categories character categories of which strings should be composed from.
 */
template <class C>
void testAccessors(QStringList (C::* getter)() const, void (C::* setter)(const QStringList &), C & object, int size, int length, const QList<QChar::Category> & categories)
{
	QStringList list = cutehmi::test::rand<QStringList>(size, length, categories);
	(object.*setter)(list);
	QCOMPARE((object.*getter)(), list);
}

/**
 * Test accessors. Overloaded function for accessors that operate on QStringList.
 *
 * @tparam C name of a class containing member access functions.
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
template <class C>
void testAccessors(QStringList (C::* getter)() const, void (C::* setter)(const QStringList &), C & object, int size = rand(0, 255), int length = rand(0, 255))
{
	testAccessors(getter, setter, object, size, length, {QChar::Letter_Uppercase, QChar::Letter_Lowercase, QChar::Number_DecimalDigit});
}

/**
 * Test accessors. Overloaded function for accessors that operate on QStringList. Performs test on default constructed object.
 *
 * @tparam C name of a class containing member access functions.
 *
 * @param getter "getter" function.
 * @param setter "setter" function.
 * @param object object to call "getter" and "setter" functions with.
 * @param size string list size.
 * @param length strings length.
 * @param categories character categories of which strings should be composed from.
 */
template <class C>
void testAccessors(QStringList (C::* getter)() const, void (C::* setter)(const QStringList &), int size, int length, const QList<QChar::Category> & categories)
{
	C object;
	testAccessors(getter, setter, object, size, length, categories);
}

/**
 * Test accessors. Overloaded function for accessors that operate on QStringList. Performs test on default constructed object.
 *
 * @tparam C name of a class containing member access functions.
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
template <class C>
void testAccessors(QStringList (C::* getter)() const, void (C::* setter)(const QStringList &), int size = rand(0, 255), int length = rand(0, 255))
{
	C object;
	testAccessors(getter, setter, object, size, length);
}

//</CuteHMI.Test-1.workaround>

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
	return equal(arr1, arr1 + size, arr2);
}

/**
 * Compare two arrays if all of their corresponding elements are inequal.
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

//(c)C: Copyright © 2018-2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
