#ifndef CUTEHMI_APPFULL_SRC_MODBUS_CONTROLWIDGET_HPP
#define CUTEHMI_APPFULL_SRC_MODBUS_CONTROLWIDGET_HPP

#include <QWidget>

namespace modbus {

class ControlWidget:
		public QWidget
{
	Q_OBJECT

	public:
		explicit ControlWidget(QWidget * parent = 0);

	signals:

	public slots:
};

}

#endif
