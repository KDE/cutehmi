#ifndef CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_PROJECT_HPP
#define CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_PROJECT_HPP

#include "internal/common.hpp"
#include "PluginLoader.hpp"
#include "ProjectModel.hpp"

#include <QQmlContext>

class QIODevice;

namespace cutehmi {
namespace base {

/**
 * Project. Encapsulates objects related to a project and provides neat interface to deal with projects.
 */
class CUTEHMI_API Project:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(PluginLoader * pluginLoader READ pluginLoader NOTIFY pluginLoaderChanged)
		Q_PROPERTY(ProjectModel * model READ model NOTIFY modelChanged)

		Project(QObject * parent = 0);

		~Project() override;

		PluginLoader * pluginLoader() const;

		ProjectModel * model() const;

		void loadXMLFile(const QString & filePath, QQmlContext * qmlContext);

	signals:
		void pluginLoaderChanged();

		void modelChanged();

	private:
		struct Members
		{
			//<principle id="cutehmi.base.Project.Members.determined_destruction_order">
			// Plugins may be used by model.
			std::unique_ptr<PluginLoader> pluginLoader{new PluginLoader};
			std::unique_ptr<ProjectModel> model{new ProjectModel};
			//</principle>
		};

		utils::MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
