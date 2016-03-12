#include "Settings.hpp"

namespace cutehmi {

Settings::Settings():
	QSettings(QSettings::IniFormat, QSettings::UserScope, "EKTERM", "CuteHMI_AppFull")
{
}

}
