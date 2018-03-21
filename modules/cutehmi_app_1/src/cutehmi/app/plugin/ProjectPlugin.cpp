#include "ProjectPlugin.hpp"
#include "PluginNodeData.hpp"
#include "ScreensNodeData.hpp"
#include "../../../../include/cutehmi/app/logging.hpp"

#include <cutehmi/xml/BackendPlugin.hpp>

#include <cutehmi/Exception.hpp>

#include <QtDebug>

namespace cutehmi {
namespace app {
namespace plugin {

void ProjectPlugin::init(ProjectNode & node)
{
	std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
	node.registerExtension(pluginNodeData->xmlBackendPlugin());
	node.data().append(std::move(pluginNodeData));
}

void ProjectPlugin::readXML(QXmlStreamReader & xmlReader, ProjectNode & node)
{
	CUTEHMI_LOG_DEBUG("Plugin 'cutehmi_app_1' starts parsing its own portion of document...");

	QStringList supportedVersions;
	supportedVersions << "http://michpolicht.github.io/CuteHMI/cutehmi_app_1/xsd/1.0/";

	xml::ParseHelper helper(& xmlReader, supportedVersions);
	helper << xml::ParseElement("cutehmi_app_1", 1, 1);

	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "cutehmi_app_1") {
			xml::ParseHelper nodeHelper(& helper);
			nodeHelper << xml::ParseElement("screens", 1, 1);
			while (nodeHelper.readNextRecognizedElement()) {
				if (xmlReader.name() == "screens")
					parseScreens(nodeHelper, node);
			}
		}
	}
}

void ProjectPlugin::writeXML(QXmlStreamWriter & xmlWriter, ProjectNode & node) const noexcept(false)
{
	Q_UNUSED(xmlWriter);
	Q_UNUSED(node);
	throw Exception("cutehmi::app::plugin::Plugin::writeXML() not implemented yet.");
}

void ProjectPlugin::parseScreens(const xml::ParseHelper & parentHelper, ProjectNode & node)
{
	std::unique_ptr<MainScreen> mainScreen;
	std::unique_ptr<ScreensNodeData> screensNodeData;

	xml::ParseHelper helper(& parentHelper);
	helper << xml::ParseElement("main_screen", {xml::ParseAttribute("source")}, 1, 1);

	const QXmlStreamReader & xmlReader = helper.xmlReader();
	while (helper.readNextRecognizedElement()) {
		if (xmlReader.name() == "main_screen")
			mainScreen.reset(new MainScreen(xmlReader.attributes().value("source").toString()));
	}

	if (!xmlReader.hasError()) {
		node.registerExtension(mainScreen.get());

		screensNodeData.reset(new ScreensNodeData(std::move(mainScreen)));
		node.data().append(std::move(screensNodeData));
	}
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
