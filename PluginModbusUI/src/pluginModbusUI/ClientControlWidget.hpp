#ifndef CUTEHMI_PLUGINMODBUSUI_SRC_PLUGINMODBUSUI_CLIENTCONTROLWIDGET_HPP
#define CUTEHMI_PLUGINMODBUSUI_SRC_PLUGINMODBUSUI_CLIENTCONTROLWIDGET_HPP

#include <QWidget>

#include "../../uic/ui_ClientControlWidget.h"

namespace cutehmi {

namespace modbus {class Client;}

namespace pluginModbusUI {

class ClientControlWidget:
	public QDialog
{
	Q_OBJECT

	public:
		explicit ClientControlWidget(modbus::Client * client, const QString & clientName, QWidget * parent = 0);

		modbus::Client * client() const;

	signals:

	public slots:
		void showAndActivate();

	private:
		modbus::Client * m_client;
		Ui::ClientControlWidget ui;
};

}
}

#endif
