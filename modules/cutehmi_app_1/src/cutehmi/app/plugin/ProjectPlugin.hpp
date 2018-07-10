#ifndef H_MODULES_CUTEHMI__APP__1_SRC_CUTEHMI_APP_PLUGIN_PROJECTPLUGIN_HPP
#define H_MODULES_CUTEHMI__APP__1_SRC_CUTEHMI_APP_PLUGIN_PROJECTPLUGIN_HPP

#include "../../../../cutehmi.metadata.hpp"

#include <cutehmi/xml/IBackendPlugin.hpp>
#include <cutehmi/xml/ParseHelper.hpp>

#include <cutehmi/IProjectPlugin.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace app {
namespace plugin {

class ProjectPlugin:
	public QObject,
	public IProjectPlugin,
	public xml::IBackendPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID CUTEHMI_IPROJECTPLUGIN_IID FILE "../../../../cutehmi.metadata.json")
	Q_INTERFACES(cutehmi::IProjectPlugin)

	public:
		// IProjectPlugin
		void init(ProjectNode & node) override;

		// xml::IBackendPlugin
		void readXML(QXmlStreamReader & xmlReader, ProjectNode & node) override;

		// xml::IBackendPlugin
		void writeXML(QXmlStreamWriter & xmlWriter, ProjectNode & node) const noexcept(false) override;

	private:
		void parseScreens(const xml::ParseHelper & parentHelper, ProjectNode & node);
};

}
}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
