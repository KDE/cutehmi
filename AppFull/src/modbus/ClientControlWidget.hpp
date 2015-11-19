#ifndef CUTEHMI_APPFULL_SRC_MODBUS_CLIENTCONTROLWIDGET_HPP
#define CUTEHMI_APPFULL_SRC_MODBUS_CLIENTCONTROLWIDGET_HPP

#include <QWidget>

#include "../uic/ui_ClientControlWidget.h"

namespace modbus {

class Client;

class ClientControlWidget:
		public QWidget
{
	Q_OBJECT

	public:
		explicit ClientControlWidget(Client * client, QWidget * parent = 0);

	signals:

	public slots:

	private:
		Client * m_client;
		Ui::ClientControlWidget ui;
};

}

#endif
