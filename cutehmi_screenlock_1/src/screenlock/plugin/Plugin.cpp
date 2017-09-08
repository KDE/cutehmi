#include "macros.hpp"
#include "Plugin.hpp"
#include "PluginNodeData.hpp"

#include <base/XMLBackendPlugin.hpp>
#include <base/Exception.hpp>

#include <QtDebug>

namespace cutehmi {
namespace screenlock {
namespace plugin {

void Plugin::init(base::ProjectNode & node)
{
    std::unique_ptr<PluginNodeData> pluginNodeData(new PluginNodeData(this));
    node.addExtension(pluginNodeData->xmlBackendPlugin());
    node.data().append(std::move(pluginNodeData));
}

void Plugin::readXML(QXmlStreamReader & xmlReader, base::ProjectNode & node)
{
    CUTEHMI_SCREENLOCK_PLUGIN_QDEBUG("Plugin 'cutehmi_screenlock_1' starts parsing its own portion of document...");

    QStringList supportedVersions;
    supportedVersions << "http://michpolicht.github.io/CuteHMI/cutehmi_screenlock_1/xsd/1.0/";

    base::xml::ParseHelper helper(& xmlReader, supportedVersions);
    helper << base::xml::ParseElement("cutehmi_screenlock_1", 1, 1);

    while (helper.readNextRecognizedElement()) {
        if (xmlReader.name() == "cutehmi_screenlock_1") {
            base::xml::ParseHelper nodeHelper(& helper);
//            nodeHelper << base::xml::ParseElement("ssh_server", 1, 1);
//            while (nodeHelper.readNextRecognizedElement()) {
//                if (xmlReader.name() == "ssh_server")
//                    parseSSHServer(nodeHelper, node);
//            }
        }
    }
}

void Plugin::writeXML(QXmlStreamWriter & xmlWriter, base::ProjectNode & node) const
{
    Q_UNUSED(xmlWriter);
    Q_UNUSED(node);
    throw base::Exception("cutehmi::screenlock::plugin::Plugin::writeXML() not implemented yet.");
}


}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
