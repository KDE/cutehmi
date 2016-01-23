#ifndef CUTEHMI_QML_CUTEHMI_MODBUS_SRC_CUTEHMIMODBUSQMLPLUGIN_HPP
#define CUTEHMI_QML_CUTEHMI_MODBUS_SRC_CUTEHMIMODBUSQMLPLUGIN_HPP

#include <QQmlExtensionPlugin>

class CuteHMIModbusQMLPlugin:
	public QQmlExtensionPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

	public:
		void registerTypes(const char * uri);
};

#endif
