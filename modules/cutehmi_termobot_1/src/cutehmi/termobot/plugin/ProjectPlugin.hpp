#ifndef H_MODULES_CUTEHMI_u_TERMOBOT_u_1_SRC_CUTEHMI_TERMOBOT_PLUGIN_PROJECTPLUGIN_HPP
#define H_MODULES_CUTEHMI_u_TERMOBOT_u_1_SRC_CUTEHMI_TERMOBOT_PLUGIN_PROJECTPLUGIN_HPP

#include "../../../../cutehmi.metadata.hpp"

#include "../DatabaseConnectionData.hpp"

#include <cutehmi/xml/IBackendPlugin.hpp>
#include <cutehmi/xml/ParseHelper.hpp>
#include <cutehmi/IProjectPlugin.hpp>

#include <QObject>

namespace cutehmi {
namespace termobot {
namespace plugin {

class ProjectPlugin : public QObject,
                      public IProjectPlugin,
                      public xml::IBackendPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID CUTEHMI_IPROJECTPLUGIN_IID FILE "../../../../cutehmi.metadata.json")
  Q_INTERFACES(cutehmi::IProjectPlugin)

public:
  // IProjectPlugin
  void init(ProjectNode &node) override;

  // xml::IBackendPlugin
  void readXML(QXmlStreamReader &xmlReader, ProjectNode &node); // override;

  // xml::IBackendPlugin
  void writeXML(QXmlStreamWriter &xmlWriter, ProjectNode &node) const
      noexcept(false); // override;

private:
  void parseTermobot(const xml::ParseHelper &parentHelper, ProjectNode &node, const QString &id, const QString &name);
  void parsePostgres(const xml::ParseHelper &parentHelper, DatabaseConnectionData & databaseConnectionData);
};

} // namespace plugin
} // namespace termobot
} // namespace cutehmi

#endif

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
