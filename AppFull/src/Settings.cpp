#include "Settings.hpp"

Settings::Settings():
	QSettings(QSettings::IniFormat, QSettings::UserScope, "EKTERM", "CuteHMI")
{
}
