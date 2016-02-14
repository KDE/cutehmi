#include "SmartStatusBar.hpp"

namespace cutehmi {

SmartStatusBar::SmartStatusBar(QWidget * parent):
	QStatusBar(parent),
	m_timeoutPerChar(INITIAL_TIMEOUT_PER_CHAR)
{
	showIdleMessage();
//	connect(this, & messageChanged, this, & setIdleForEmpty);
}

int SmartStatusBar::timeoutPerChar() const
{
	return m_timeoutPerChar;
}

void SmartStatusBar::setTimeoutPerChar(int timeout)
{
	m_timeoutPerChar = timeout;
}

void SmartStatusBar::showIdleMessage()
{
//	showMessage(QObject::tr("Idle"));
}

void SmartStatusBar::showAutoMessage(const QString & message)
{
	showMessage(message, message.length() * m_timeoutPerChar);
}

void SmartStatusBar::setIdleForEmpty(const QString & message)
{
	if (message.isEmpty())
		showIdleMessage();
}

}
