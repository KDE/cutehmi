#ifndef CUTEHMI_APPFULL_SRC_MODBUS_CONFIGURATIONDIALOG_HPP
#define CUTEHMI_APPFULL_SRC_MODBUS_CONFIGURATIONDIALOG_HPP

#include <QDialog>

namespace modbus {

namespace Ui { class ConfigurationDialog; }

class ConfigurationDialog:
		public QDialog
{
	Q_OBJECT

	public:
		explicit ConfigurationDialog(QWidget * parent = 0);

		~ConfigurationDialog();

	private:
		Ui::ConfigurationDialog * ui;
};

}

#endif
