#ifndef H_MODULES_CUTEHMI__TEST__1_INCLUDE_CUTEHMI_TEST_RANDOM_HPP
#define H_MODULES_CUTEHMI__TEST__1_INCLUDE_CUTEHMI_TEST_RANDOM_HPP

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
 */
template <typename T, typename E = SeededEngine<std::mt19937>>
typename std::enable_if<std::is_integral<T>::value, T>::type rand(T from = std::numeric_limits<T>::min(), T to = std::numeric_limits<T>::max())
{
	static E engine;    // Use static variable to prevent frequent allocation/deallocation ("mt19937 use 5000 bytes of memory for each creation (which is bad for performance if we create it too frequently)" -- https://github.com/effolkronium/random).

	std::uniform_int_distribution<T> distribution(from, to);

	return distribution(engine);
}

}
}

#endif
