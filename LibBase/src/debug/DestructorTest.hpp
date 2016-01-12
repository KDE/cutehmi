#ifndef CUTEHMI_LIBBASE_SRC_DEBUG_DESTRUCTORTEST_HPP
#define CUTEHMI_LIBBASE_SRC_DEBUG_DESTRUCTORTEST_HPP

#include <iostream>

#include <typeinfo>

namespace debug {

/**
 * Destructor test. Maintaining object lifetime in Qt can be tricky. Object trees not always make life
 * easier and documentation of functions, which may reparent objects, can be enigmatic. This class
 * is provide for easier testing of object destruction order. It simply prints debug message
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

#endif

