#include "ClientControlWidget.hpp"

#include <modbus/Client.hpp>

namespace modbus {
namespace widgets {

ClientControlWidget::ClientControlWidget(modbus::Client * client, QWidget * parent):
	QWidget(parent),
	m_client(client)
{
	ui.setupUi(this);
	connect(ui.connectButton, & QPushButton::clicked, client, & modbus::Client::connect);
	connect(ui.disconnectButton, & QPushButton::clicked, client, & modbus::Client::disconnect);
}

}
}
