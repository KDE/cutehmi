#include "ClientControlWidget.hpp"
#include "Plugin.hpp"

#include <modbus/Client.hpp>

namespace cutehmi {
namespace pluginModbusUI {

ClientControlWidget::ClientControlWidget(modbus::Client * client, const QString & clientName, QWidget * parent):
	QDialog(parent),
	m_client(client)
{
	ui.setupUi(this);
	setWindowTitle(QCoreApplication::applicationName() + " - " + clientName + " - Control");
	connect(ui.connectButton, & QPushButton::clicked, client, & modbus::Client::connect);
	connect(ui.disconnectButton, & QPushButton::clicked, client, & modbus::Client::disconnect);
	connect(ui.pollButton, & QPushButton::clicked, client, & modbus::Client::readAll);
}

modbus::Client * ClientControlWidget::client() const
{
	return m_client;
}

void ClientControlWidget::showAndActivate()
{
	//<workaround id="PluginModbusUI-1" target="Qt" cause="bug">
	hide();
	show();
	//</workaround>
	raise();
}

}
}
