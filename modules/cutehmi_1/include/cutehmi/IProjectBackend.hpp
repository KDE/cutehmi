#ifndef CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_IBACKEND_HPP
#define CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_IBACKEND_HPP

#include "ProjectNode.hpp"
#include "ProjectPluginLoader.hpp"

namespace cutehmi {

/**
 * Backend interface.
 */
class CUTEHMI_API IProjectBackend
{
	public:
		virtual void load(const ProjectPluginLoader & pluginLoader, ProjectNode & rootNode) noexcept(false) = 0;

	protected:
		virtual ~IProjectBackend() = default; // Making dtor virtual for plugin interface as in Qt docs.

		IProjectBackend() = default;
};

}

#endif
