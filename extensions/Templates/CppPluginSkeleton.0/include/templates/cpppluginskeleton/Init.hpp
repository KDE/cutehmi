#ifndef H_EXTENSIONS_TEMPLATES_CPPPLUGINSKELETON_0_INCLUDE_TEMPLATES_CPPPLUGINSKELETON_INIT_HPP
#define H_EXTENSIONS_TEMPLATES_CPPPLUGINSKELETON_0_INCLUDE_TEMPLATES_CPPPLUGINSKELETON_INIT_HPP

// This file has been initially autogenerated by 'cutehmi.skeleton.cpp' Qbs module.

#include "internal/platform.hpp"
#include <cutehmi/Initializer.hpp>

namespace templates {
namespace cpppluginskeleton {

/**
 * %Init. This class performs initialization of the extension.
 *
 * Normally it is not advisable to create custom instances of this class as extension provides an instance on its own. This can be
 * invalidated particulary by static builds in which case a global variable may not get into resulting binary.
 */
class TEMPLATES_CPPPLUGINSKELETON_API Init final:
	public ::cutehmi::Initializer<Init>
{
	public:
		/**
		 * Default constructor.
		 */
		Init();
};

}
}

#endif
