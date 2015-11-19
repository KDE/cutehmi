#include "ClientControlWidget.hpp"

namespace modbus {

ClientControlWidget::ClientControlWidget(Client * client, QWidget * parent):
	QWidget(parent),
	m_client(client)
{
	ui.setupUi(this);
}

}
