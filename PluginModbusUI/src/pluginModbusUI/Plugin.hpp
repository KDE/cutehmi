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
