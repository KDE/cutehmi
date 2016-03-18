#ifndef CUTEHMI_PLUGINMODBUSUI_SRC_PLUGINMODBUSUI_PLUGIN_HPP
#define CUTEHMI_PLUGINMODBUSUI_SRC_PLUGINMODBUSUI_PLUGIN_HPP

#include <widgets/IUIPlugin.hpp>

#include <QObject>

namespace cutehmi {
namespace pluginModbusUI {

class Plugin:
	public QObject,
	public widgets::IUIPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "CuteHMI.PluginModbusUI" FILE "PluginModbusUI.json")
	Q_INTERFACES(cutehmi::widgets::IUIPlugin)

	public:
		static QString ProjectName();

		Plugin();

		void setParentWidget(QWidget * widget) override;

		void visit(base::ProjectModel::Node & node) override;

	private:
		QWidget * m_parentWidget;
		static QString M_ProjectName;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
