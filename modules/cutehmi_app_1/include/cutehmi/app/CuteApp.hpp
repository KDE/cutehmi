#ifndef H_MODULES_CUTEHMI__APP__1_INCLUDE_CUTEHMI_APP_CUTEAPP_HPP
#define H_MODULES_CUTEHMI__APP__1_INCLUDE_CUTEHMI_APP_CUTEAPP_HPP

#include "internal/common.hpp"

#include <QApplication>
#include <QTime>
#include <QTimer>

namespace cutehmi {
namespace app {

class CUTEHMI_APP_API CuteApp:
	//<workaround id="cutehmi_app_1-1" target="Qt" cause="bug">
	public QApplication
	// Instead of:
	// public QGuiApplication
	//</workaround>
{
	typedef QApplication Parent;

	Q_OBJECT

	public:
		//<workaround ref="cutehmi_lockscreen_1_qml-1" target="Qt" cause="design">
		static constexpr int IDLE_MEASURE_INTERVAL = 1000;	///< Idle measurement update interval [milliseconds].
		//</workaround>

		//<workaround ref="cutehmi_lockscreen_1_qml-1" target="Qt" cause="design">
		Q_PROPERTY(double idle READ idle NOTIFY idleChanged)

		Q_PROPERTY(bool idleMeasureEnabled READ idleMeasureEnabled WRITE setIdleMeasureEnabled NOTIFY idleMeasureEnabledChanged)
		//</workaround>

		CuteApp(int & argc, char ** argv);

		//<workaround ref="cutehmi_lockscreen_1_qml-1" target="Qt" cause="design">
		double idle() const;

		bool idleMeasureEnabled() const;

		void setIdleMeasureEnabled(bool idleMeasureEnabled);

		bool notify(QObject * receiver, QEvent * event) override;
		//</workaround>

	signals:
		//<workaround ref="cutehmi_lockscreen_1_qml-1" target="Qt" cause="design">
		void idleChanged();

		void idleMeasureEnabledChanged();
		//</workaround>

	private slots:
		//<workaround ref="cutehmi_lockscreen_1_qml-1" target="Qt" cause="design">
		void updateIdleTime();
		//</workaround>

	private:
		//<workaround ref="cutehmi_lockscreen_1_qml-1" target="Qt" cause="design">
		void setIdle(double idle);
		//</workaround>

	private:
		struct Members
		{
			//<workaround ref="cutehmi_lockscreen_1_qml-1" target="Qt" cause="design">
			int notifyEventCtr;
			double idle;	///< Idle time [seconds].
			bool idleMeasureEnabled;
			QTimer updateTimer;
			QTime idleTime;
			//</workaround>

			Members();
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
