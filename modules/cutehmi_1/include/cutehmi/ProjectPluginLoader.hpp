#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_PROJECTPLUGINLOADER_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_PROJECTPLUGINLOADER_HPP

#include "internal/common.hpp"
#include "Error.hpp"
#include "ExceptionMixin.hpp"
#include "Plugin.hpp"

#include <QPluginLoader>

#include <memory>

namespace cutehmi {

class ProjectNode;

namespace internal { class PluginLoader; }

/**
 * Project plugin loader. Objects of this class can not be instantiated directly.
 */
class CUTEHMI_API ProjectPluginLoader
{
	friend class Project;

	public:
		class MissingInterfaceException:
			public ExceptionMixin<MissingInterfaceException>
		{
			typedef ExceptionMixin<MissingInterfaceException> Parent;

			public:
				MissingInterfaceException(const QString & binary, const QString & pluginVersion, const QString & interface):
					Parent(tr("Plugin '%1' version '%2' does not implement required interface '%3'.").arg(binary).arg(pluginVersion).arg(interface))
				{
				}
		};

		/**
		 * Add plugin node to the given parent node. Beside creating a node, this function will load a plugin and
		 * initialize it. Plugin object is accessible through an extension mechanism of newly created ProjectNode
		 * (call `cutehmi::ProjectNode::extension(cutehmi::Plugin::staticMetaObject.className())` to access Plugin object).
		 * @param name name of the plugin. Suffix 'd' will be appended to the binary name in the debug mode.
		 * @param reqMinor minimal required minor version of the plugin.
		 * @param parentNode node to which plugin node should be added.
		 * @return newly created plugin node. Exception will be thrown in case of failure.
		 */
		ProjectNode * addPluginNode(const QString & name, int reqMinor, ProjectNode & parentNode) const noexcept(false);

	private:
		explicit ProjectPluginLoader(internal::PluginLoader * pluginLoader);

	private:
		struct Members
		{
			internal::PluginLoader * pluginLoader;
		};

		MPtr<Members> m;
};

}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
