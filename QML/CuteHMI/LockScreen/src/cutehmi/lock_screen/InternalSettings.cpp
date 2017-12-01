#include "InternalSettings.hpp"

namespace cutehmi {
namespace lockscreen {

InternalSettings::InternalSettings(QObject *parent) : QObject(parent)
{
	m_settings = new QSettings(this);
	m_settings->beginGroup("cutehmi_lockscreen_1");
}

void InternalSettings::setActivated(const bool & activated)
{
	if (activated != getActivated())
	{
		m_settings->setValue("activated", activated);
		emit activatedChanged(activated);
	}
}

void InternalSettings::setTimeout(const int & timeout)
{
	if (timeout != getTimeout())
	{
		m_settings->setValue("timeout", timeout);
		emit timeoutChanged(timeout);
	}
}

bool InternalSettings::getActivated() const
{
	return m_settings->value("activated", true).toBool();
}

int InternalSettings::getTimeout() const
{
	return m_settings->value("timeout", 90).toInt();
}

}
}
