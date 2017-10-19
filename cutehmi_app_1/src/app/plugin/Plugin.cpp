#include "macros.hpp"
#include "Plugin.hpp"
#include "PluginNodeData.hpp"
#include "ScreensNodeData.hpp"

#include <base/XMLBackendPlugin.hpp>
#include <base/Exception.hpp>

#include <QtDebug>

namespace cutehmi {
namespace app {
namespace plugin {

void Plugin::init(base::ProjectNode & node)
{
	std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
	node.addExtension(pluginNodeData->xmlBackendPlugin());
	node.data().append(std::move(pluginNodeData));
}

void Plugin::readXML(QXmlStreamReader & xmlReader, base::ProjectNode & node)
{
	CUTEHMI_APP_1_QDEBUG("Plugin 'cutehmi_app_1' starts parsing its own portion of document...");

	QStringList supportedVersions;
	supportedVersions << "http://michpolicht.github.io/CuteHMI/cutehmi_app_1/xsd/1.0/";

	base::xml::ParseHelper helper(& xmlReader, supportedVersions);
	helper << base::xml::ParseElement("cutehmi_app_1", 1, 1);

	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "cutehmi_app_1") {
			base::xml::ParseHelper nodeHelper(& helper);
			nodeHelper << base::xml::ParseElement("screens", 1, 1);
			while (nodeHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "screens")
					parseScreens(nodeHelper, node);
			}
		}
	}
}

void Plugin::writeXML(QXmlStreamWriter & xmlWriter, base::ProjectNode & node) const
{
	Q_UNUSED(xmlWriter);
	Q_UNUSED(node);
	throw base::Exception("cutehmi::app::plugin::Plugin::writeXML() not implemented yet.");
}

void Plugin::parseScreens(const base::xml::ParseHelper & parentHelper, base::ProjectNode & node)
{
	std::unique_ptr<MainScreen> mainScreen;
	std::unique_ptr<ScreensNodeData> screensNodeData;

	base::xml::ParseHelper helper(& parentHelper);
	helper << base::xml::ParseElement("main_screen", {base::xml::ParseAttribute("source")}, 1, 1);

	QXmlStreamReader & xmlReader = *helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "main_screen")
			mainScreen.reset(new MainScreen(xmlReader.attributes().value("source").toString()));
	}

	node.addExtension(mainScreen.get());

	screensNodeData.reset(new ScreensNodeData(std::move(mainScreen)));
	node.data().append(std::move(screensNodeData));
}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
