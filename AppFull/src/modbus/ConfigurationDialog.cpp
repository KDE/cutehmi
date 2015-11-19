#include "ConfigurationDialog.hpp"
#include "ui_ConfigurationDialog.h"

namespace modbus {

ConfigurationDialog::ConfigurationDialog(QWidget * parent):
	QDialog(parent),
	ui(new Ui::ConfigurationDialog)
{
	ui->setupUi(this);
}

ConfigurationDialog::~ConfigurationDialog()
{
	delete ui;
}

}
