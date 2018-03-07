#include "Settings.hpp"

namespace cutehmi {
namespace lockscreen {
namespace qml {

Settings::Settings(QObject *parent) : QObject(parent)
{
	m_settings = new QSettings(this);
	m_settings->beginGroup("cutehmi_lockscreen_1");
}

void Settings::setActivated(const bool & activated)
{
	if (activated != getActivated())
	{
		m_settings->setValue("activated", activated);
		emit activatedChanged(activated);
	}
}

void Settings::setTimeout(const int & timeout)
{
	if (timeout != getTimeout())
	{
		m_settings->setValue("timeout", timeout);
		emit timeoutChanged(timeout);
	}
}

bool Settings::getActivated() const
{
	return m_settings->value("activated", true).toBool();
}

int Settings::getTimeout() const
{
	return m_settings->value("timeout", 90).toInt();
}

}
}
}

//(c)WZMP: Copyright © 2018, Wojciech Zygmuntowicz, Michal Policht. All rights reserved.
//(c)WZMP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
