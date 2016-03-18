#ifndef CUTEHMI_APPFULL_SRC_SMARTSTATUSBAR_HPP
#define CUTEHMI_APPFULL_SRC_SMARTSTATUSBAR_HPP

#include <QStatusBar>

namespace cutehmi {

class SmartStatusBar:
	public QStatusBar
{
	public:
		static const int INITIAL_TIMEOUT_PER_CHAR = 500;

		SmartStatusBar(QWidget * parent = 0);

		~SmartStatusBar() override = default;

		int timeoutPerChar() const;

		void setTimeoutPerChar(int timeout);

		void showIdleMessage();

	public slots:
		void showAutoMessage(const QString & message);

	private slots:
		void setIdleForEmpty(const QString & message);

	private:
		int m_timeoutPerChar;
};

}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
