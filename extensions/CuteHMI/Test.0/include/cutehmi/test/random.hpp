#ifndef H_EXTENSIONS_CUTEHMI_TEST_0_INCLUDE_CUTEHMI_TEST_RANDOM_HPP
#define H_EXTENSIONS_CUTEHMI_TEST_0_INCLUDE_CUTEHMI_TEST_RANDOM_HPP

#include "IsIntType.hpp"

#include <QChar>
#include <QString>
#include <QList>
#include <QMultiHash>

#include <random>
#include <chrono>
#include <limits>
#include <type_traits>

namespace cutehmi {
namespace test {

/**
 * Seeded engine. This class extends random generator class specified by @a E
 * template parameter and behaves exactly like extended class, except it seeds
 * itself within a constructor.
 * @tparam E random number generator engine.
 */
template <class E = std::mt19937>
class SeededEngine :
	public E
{
	public:
		/**
		 * Default constructor.
		 */
		SeededEngine();
};

template <class E>
SeededEngine<E>::SeededEngine()
{
	std::random_device randomDevice;

	// Some implementations do not have non-deterministic std::random_device.
	// Check out entropy of std::random_device. If it's zero, then fallback to
	// time-based seed.
	//
	// Note that sometimes it's std::random_device::entropy(), which is not
	// implemented properly, accodring to _cppreference.com_. Still use
	// time-based fallback in such cases, as we won't do workarounds.
	//
	// "This function is not fully implemented in some standard libraries. For
	//  example, LLVM libc++ always returns zero even though the device is
	//  non-deterministic. In comparison, Microsoft Visual C++ implementation
	//  always returns 32, and boost.random returns 10.
	//  The entropy of the Linux kernel device /dev/urandom may be obtained
	//  using ioctl RNDGETENTCNT - that's what std::random_device::entropy() in
	//  GNU libstdc++ uses as of version 8.1"
	//  -- https://en.cppreference.com/w/cpp/numeric/random/random_device/entropy
	if (randomDevice.entropy() != 0.0)
		E::seed(randomDevice());
	else
		E::seed(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
}

/**
 * Generate random integer using uniform distribution.
 * @tparam T integer type.
 * @tparam E random number generator engine.
 * @param from lower bound of a set of generated random numbers.
 * @param from upper bound of a set of generated random numbers.
 * @return randomly generated integer.
 */
template <typename T, typename E = SeededEngine<std::mt19937>>
typename std::enable_if<IsIntType<T>::value, T>::type rand(T from = std::numeric_limits<T>::min(), T to = std::numeric_limits<T>::max())
{
	static E engine;    // Use static variable to prevent frequent allocation/deallocation ("mt19937 use 5000 bytes of memory for each creation (which is bad for performance if we create it too frequently)" -- https://github.com/effolkronium/random).

	std::uniform_int_distribution<T> distribution(from, to);

	return distribution(engine);
}

/**
 * Generate random floating point number using uniform distribution.
 * @tparam T floating point number type.
 * @tparam E random number generator engine.
 * @param from lower bound of a set of generated random numbers.
 * @param from upper bound of a set of generated random numbers.
 * @return randomly generated floating point number.
 */
template <typename T, typename E = SeededEngine<std::mt19937>>
typename std::enable_if<std::is_floating_point<T>::value, T>::type rand(T from = std::numeric_limits<T>::min(), T to = std::numeric_limits<T>::max())
{
	static E engine;    // Use static variable to prevent frequent allocation/deallocation ("mt19937 use 5000 bytes of memory for each creation (which is bad for performance if we create it too frequently)" -- https://github.com/effolkronium/random).

	std::uniform_real_distribution<T> distribution(from, to);

	return distribution(engine);
}

/**
 * Generate random Boolean value using Bernoulli distribution.
 * @tparam T boolean type.
 * @tparam E random number generator engine.
 * @param p propbablity of generating @p true.
 * @return one of the Boolean values: @p true or @p false.
 */
template <typename T, typename E = SeededEngine<std::mt19937>>
typename std::enable_if<std::is_same<T, bool>::value, T>::type rand(double p = 0.5)
{
	static E engine;    // Use static variable to prevent frequent allocation/deallocation ("mt19937 use 5000 bytes of memory for each creation (which is bad for performance if we create it too frequently)" -- https://github.com/effolkronium/random).

	std::bernoulli_distribution distribution(p);

	return distribution(engine);
}

/**
 * Generate random character.
 * @tparam T QChar type.
 * @tparam E random number generator engine.
 * @param category character category.
 * @return random character.
 */
template <typename T, typename E = SeededEngine<std::mt19937>>
typename std::enable_if<std::is_same<T, QChar>::value, QChar>::type rand(QChar::Category category)
{
	static E engine;    // Use static variable to prevent frequent allocation/deallocation ("mt19937 use 5000 bytes of memory for each creation (which is bad for performance if we create it too frequently)" -- https://github.com/effolkronium/random).
	static QMultiHash<int, QChar> categorySets;		// Key denotes category of specific charecters.

	if (categorySets.empty()) {
		// Initialize categorized sets of characters.
		for (char16_t c = 0; c < std::numeric_limits<char16_t>::max(); c++)
			categorySets.insert(QChar::category(c), c);
		categorySets.insert(QChar::category(std::numeric_limits<char16_t>::max()), std::numeric_limits<char16_t>::max());
	}

	return categorySets.values(category).at(rand(0, categorySets.values(category).size() - 1));
}

/**
 * Generate random string.
 * @tparam T QString type.
 * @tparam E random number generator engine.
 * @param length string length.
 * @param categories character categories of which string should be composed from.
 * @return randomly generated string.
 */
template <typename T, typename E = SeededEngine<std::mt19937>>
typename std::enable_if<std::is_same<T, QString>::value, T>::type rand(int length = rand(0, 255), QList<QChar::Category> categories = {QChar::Letter_Uppercase, QChar::Letter_Lowercase, QChar::Number_DecimalDigit})
{
	static E engine;    // Use static variable to prevent frequent allocation/deallocation ("mt19937 use 5000 bytes of memory for each creation (which is bad for performance if we create it too frequently)" -- https://github.com/effolkronium/random).

	QString result("");
	for (int i = 0; i < length; i++)
		result.append(rand<QChar>(categories.at(rand(0, categories.size() - 1))));

	return result;
}

/**
 * Generate random string list.
 * @tparam T QStringList type.
 * @tparam E random number generator engine.
 * @param size string list size.
 * @param length strings length.
 * @param categories character categories of which strings should be composed from.
 * @return randomly generated string list.
 */
template <typename T, typename E = SeededEngine<std::mt19937>>
typename std::enable_if<std::is_same<T, QStringList>::value, T>::type rand(int size = rand(0, 255), int length = rand(0, 255), QList<QChar::Category> categories = {QChar::Letter_Uppercase, QChar::Letter_Lowercase, QChar::Number_DecimalDigit})
{
	static E engine;    // Use static variable to prevent frequent allocation/deallocation ("mt19937 use 5000 bytes of memory for each creation (which is bad for performance if we create it too frequently)" -- https://github.com/effolkronium/random).

	QStringList result;
	for (int i = 0; i < size; i++)
		result.append(rand<QString>(length, categories));

	return result;
}

/**
 * Randomize array.
 * @tparam T type of array elements.
 * @tparam E random number genererator engine.
 * @tparam ARGS arguments to be passed to underlying rand() function.
 * @param ptr array pointer.
 * @param size array size.
 * @param arguments to be passed to underlying rand() function for each array
 * element.
 */
template <typename T, typename E = SeededEngine<std::mt19937>, typename... ARGS>
void rand(T * ptr, std::size_t size, ARGS... args)
{
	while (size > 0) {
		*ptr = rand<T, E>(args...);
		ptr++;
		size--;
	}
}

}
}

#endif

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
