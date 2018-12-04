#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_PROJECT_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_PROJECT_HPP

#include "internal/common.hpp"
#include "internal/PluginLoader.hpp"
#include "ProjectModel.hpp"
#include "IProjectBackend.hpp"

#include <QQmlListProperty>

class QIODevice;

namespace cutehmi {

/**
 * %Project. Encapsulates objects related to a project and provides neat
 * interface to deal with projects.
 */
class CUTEHMI_API Project:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(ProjectModel * model READ model NOTIFY modelChanged)
		Q_PROPERTY(QQmlListProperty<cutehmi::Plugin> plugins READ plugins NOTIFY pluginsChanged)

		Project(QObject * parent = nullptr);

		~Project() override;

		ProjectModel * model() const;

		const QQmlListProperty<Plugin> & plugins() const;

		void load(IProjectBackend & backend) noexcept(false);

		void reset();

	signals:
		void modelChanged();

		void pluginsChanged();

	protected:
		internal::PluginLoader * pluginLoader() const;

	private:
		struct Members
		{
			//<principle id="cutehmi::Project::Members-determined_destruction_order">
			std::unique_ptr<internal::PluginLoader> pluginLoader{new internal::PluginLoader}; // Plugins may be used by 'model'.
			std::unique_ptr<QQmlListProperty<Plugin>> plugins{new QQmlListProperty<Plugin>(pluginLoader.get(), const_cast<internal::PluginLoader::LoadedPluginsContainer *>(pluginLoader.get()->loadedPlugins()), Project::PluginsCount, Project::PluginsAt)};
			std::unique_ptr<ProjectModel> model{new ProjectModel};
			//</principle>
		};

		static int PluginsCount(QQmlListProperty<Plugin> * property);

		static Plugin * PluginsAt(QQmlListProperty<Plugin> * property, int index);

		MPtr<Members> m;
};

}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
