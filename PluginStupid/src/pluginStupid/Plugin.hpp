#ifndef CUTEHMI_PLUGINSTUPID_SRC_PLUGINSTUPID_PLUGIN_HPP
#define CUTEHMI_PLUGINSTUPID_SRC_PLUGINSTUPID_PLUGIN_HPP

#include <base/IPLCPlugin.hpp>

#include <stupid/Client.hpp>

#include <QObject>
#include <QSqlDatabase>

#include <memory>

namespace cutehmi {
namespace pluginStupid {

class Plugin:
	public QObject,
	public base::IPLCPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "CuteHMI.PluginStupid" FILE "PluginStupid.json")
	Q_INTERFACES(cutehmi::base::IPLCPlugin)

	public:
		base::Error readXML(QXmlStreamReader & xmlReader, base::ProjectModel::Node & node) override;

		base::Error writeXML(QXmlStreamWriter & xmlWriter) const override;

	private:
		base::Error postgreSQLFromXML(QXmlStreamReader & xmlReader, const QString & connectionName);
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
