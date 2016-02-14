#ifndef CUTEHMI_APPFULL_SRC_SETTINGS_HPP
#define CUTEHMI_APPFULL_SRC_SETTINGS_HPP

#include <QSettings>

namespace cutehmi {

class Settings:
	public QSettings
{
	public:
		Settings();
};

}

#endif
