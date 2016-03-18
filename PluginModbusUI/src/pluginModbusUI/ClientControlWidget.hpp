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
		ClientControlWidget(modbus::Client * client, const QString & clientName, QWidget * parent = 0);

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

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
