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

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
