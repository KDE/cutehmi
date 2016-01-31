#ifndef CUTEHMI_PLUGINMODBUSUI_SRC_MODBUS_UI_CLIENTCONTROLWIDGET_HPP
#define CUTEHMI_PLUGINMODBUSUI_SRC_MODBUS_UI_CLIENTCONTROLWIDGET_HPP

#include <QWidget>

#include "../../../uic/ui_ClientControlWidget.h"

namespace modbus {

class Client;

namespace ui {

class ClientControlWidget:
	public QWidget
{
	Q_OBJECT

	public:
		explicit ClientControlWidget(modbus::Client * client, QWidget * parent = 0);

	signals:

	public slots:

	private:
		modbus::Client * m_client;
		Ui::ClientControlWidget ui;
};

}
}

#endif
