#ifndef H_MODULES_CUTEHMI__TEST__1_INCLUDE_CUTEHMI_TEST_ISINTTYPE_HPP
#define H_MODULES_CUTEHMI__TEST__1_INCLUDE_CUTEHMI_TEST_ISINTTYPE_HPP

#include "IsAnyOfTypes.hpp"

namespace cutehmi {
namespace test {

/**
 * Check if template parameter is of integer type.
 * @tparam T parameter to check.
 * @return if @a T is an integer, structure provides a member constant @a value
 * equal to @p true. Otherwise @a value is @p false.
 */
template<typename T>
struct IsIntType:
	IsAnyOfTypes<T, short, int, long, long long, unsigned short, unsigned int, unsigned long, unsigned long long>
{
};

}
}

#endif
