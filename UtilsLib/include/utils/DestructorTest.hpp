#ifndef CUTEHMI_UTILSLIB_INCLUDE_UTILS_DESTRUCTORTEST_HPP
#define CUTEHMI_UTILSLIB_INCLUDE_UTILS_DESTRUCTORTEST_HPP

#include <iostream>

#include <typeinfo>

namespace cutehmi {
namespace utils {

/**
 * Destructor test. Maintaining object lifetime in Qt can be tricky. Object trees not always make life
 * easier and documentation of functions, which may reparent objects, can be enigmatic. This class
 * is provided for simple testing of object destruction order. It simply prints debug message
 * to the standard error.
 */
template <class DERIVED>
class DestructorTest : public DERIVED
{
	public:
		using DERIVED::DERIVED;

		/**
		 * Destructor. Prints basic debug message ("class@object destructor has been called") to the standard error.
		 */
		virtual ~DestructorTest();
};

template <class DERIVED>
DestructorTest<DERIVED>::~DestructorTest()
{
	std::cerr << typeid(DERIVED).name() << "@" << this << " destructor has been called\n";
}

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
