#ifndef CUTEHMI_PLUGINMODBUSUI_SRC_PLUGINMODBUSUI_PLUGIN_HPP
#define CUTEHMI_PLUGINMODBUSUI_SRC_PLUGINMODBUSUI_PLUGIN_HPP

#include <plugin/IProjectModelVisitor.hpp>

#include <QObject>

namespace pluginModbusGUI {

class Plugin:
	public QObject,
	public plugin::IProjectModelVisitor
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "CuteHMI.PluginModbusGUI" FILE "PluginModbusGUI.json")
	Q_INTERFACES(plugin::IProjectModelVisitor)

	public:
		static QString ProjectName();

		void visit(base::ProjectModel::Node & node) override;

	private:
		static QString M_ProjectName;
};

}

#endif
