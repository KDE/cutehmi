#ifndef CUTEHMI_PLUGINSTUPID_SRC_STUPID_PLUGIN_PLUGIN_HPP
#define CUTEHMI_PLUGINSTUPID_SRC_STUPID_PLUGIN_PLUGIN_HPP

#include <base/IPlugin.hpp>
#include <base/IXMLBackendPlugin.hpp>
#include <base/xml/ParseHelper.hpp>

#include <stupid/Client.hpp>
#include <stupid/internal/DatabaseConnectionData.hpp>

#include <QObject>
#include <QSqlDatabase>

#include <memory>

namespace cutehmi {
namespace stupid {
namespace plugin {

class Plugin:
	public QObject,
	public base::IPlugin,
	public base::IXMLBackendPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID CUTEHMI_BASE_IPLUGIN_IID FILE "PluginStupid.json")
	Q_INTERFACES(cutehmi::base::IPlugin)

	public:
		static constexpr const char * NAMESPACE_URI = "http://stupid.cutehmi";

		// base::IPlugin
		void init(base::ProjectNode & node) override;

		// base::IXMLBackendPlugin
		void readXML(QXmlStreamReader & xmlReader, base::ProjectNode & node) override;

		// base::IXMLBackendPlugin
		void writeXML(QXmlStreamWriter & xmlWriter, base::ProjectNode & node) const override;

	private:
		void parseStupid(const base::xml::ParseHelper & parentHelper, base::ProjectNode & node, const QString & id, const QString & name);

		void parsePostgreSQL(const base::xml::ParseHelper & parentHelper, stupid::DatabaseConnectionData & dbData);
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
