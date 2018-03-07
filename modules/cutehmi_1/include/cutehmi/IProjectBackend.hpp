#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_IPROJECTBACKEND_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_IPROJECTBACKEND_HPP

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
