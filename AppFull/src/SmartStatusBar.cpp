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

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
