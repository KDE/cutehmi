#include "ClientControlWidget.hpp"
#include "Plugin.hpp"

#include <modbus/Client.hpp>

namespace pluginModbusGUI {

ClientControlWidget::ClientControlWidget(modbus::Client * client, const QString & clientName, QWidget * parent):
	QDialog(parent),
	m_client(client)
{
	ui.setupUi(this);
	setWindowTitle(clientName + " - Control - " + Plugin::ProjectName() + " - " + QCoreApplication::applicationName());
	connect(ui.connectButton, & QPushButton::clicked, client, & modbus::Client::connect);
	connect(ui.disconnectButton, & QPushButton::clicked, client, & modbus::Client::disconnect);
	connect(ui.pollButton, & QPushButton::clicked, client, & modbus::Client::readAll);
}

}
