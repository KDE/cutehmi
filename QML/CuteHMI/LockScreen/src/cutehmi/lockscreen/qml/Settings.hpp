#ifndef H_QML_CUTEHMI_LOCKSCREEN_SRC_CUTEHMI_LOCKSCREEN_QML_SETTINGS_HPP
#define H_QML_CUTEHMI_LOCKSCREEN_SRC_CUTEHMI_LOCKSCREEN_QML_SETTINGS_HPP

#include <QSettings>
#include <QObject>

namespace cutehmi {
namespace lockscreen {
namespace qml {

class Settings : public QObject
{
		Q_OBJECT
	public:
		explicit Settings(QObject *parent = nullptr);

		Q_PROPERTY(bool activated READ getActivated WRITE setActivated NOTIFY activatedChanged)

		Q_PROPERTY(int timeout READ getTimeout WRITE setTimeout NOTIFY timeoutChanged)

		void setActivated(const bool & activated);

		void setTimeout(const int & timeout);

		bool getActivated() const;

		int getTimeout() const;

	signals:
		void activatedChanged(const bool & newActivated);

		void timeoutChanged(const int & newTimeout);

	public slots:

	private:

		QSettings * m_settings;
};

}
}
}

#endif

//(c)WZMP: Copyright © 2018, Wojciech Zygmuntowicz, Michal Policht. All rights reserved.
//(c)WZMP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
