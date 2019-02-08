#ifndef H_EXTENSIONS_CUTEHMI_APP_2_INCLUDE_CUTEHMI_APP_CUTEAPP_HPP
#define H_EXTENSIONS_CUTEHMI_APP_2_INCLUDE_CUTEHMI_APP_CUTEAPP_HPP

#include "internal/common.hpp"

#include <QApplication>
#include <QTime>
#include <QTimer>

namespace cutehmi {
namespace app {

/**
 * %CuteHMI application. This class extends QApplication to provide idle measurment.
 */
class CUTEHMI_APP_API CuteApp:
	//<CuteHMI.App-1.workaround target="Qt" cause="bug">
	public QApplication
	// Instead of:
	// public QGuiApplication
	//</CuteHMI.App-1.workaround>
{
	typedef QApplication Parent;

	Q_OBJECT

	public:
		//<CuteHMI.LockScreen-1.workaround target="Qt" cause="design">
		static constexpr int IDLE_MEASURE_INTERVAL = 1000;	///< Idle measurement update interval [milliseconds].
		//</CuteHMI.LockScreen-1.workaround>

		//<CuteHMI.LockScreen-1.workaround target="Qt" cause="design">
		Q_PROPERTY(double idle READ idle NOTIFY idleChanged)

		Q_PROPERTY(bool idleMeasureEnabled READ idleMeasureEnabled WRITE setIdleMeasureEnabled NOTIFY idleMeasureEnabledChanged)
		//</CuteHMI.LockScreen-1.workaround>

		CuteApp(int & argc, char ** argv);

		//<CuteHMI.LockScreen-1.workaround target="Qt" cause="design">
		double idle() const;

		bool idleMeasureEnabled() const;

		void setIdleMeasureEnabled(bool idleMeasureEnabled);

		bool notify(QObject * receiver, QEvent * event) override;
		//</CuteHMI.LockScreen-1.workaround>

	signals:
		//<CuteHMI.LockScreen-1.workaround target="Qt" cause="design">
		void idleChanged();

		void idleMeasureEnabledChanged();
		//</CuteHMI.LockScreen-1.workaround>

	private slots:
		//<CuteHMI.LockScreen-1.workaround target="Qt" cause="design">
		void updateIdleTime();
		//</CuteHMI.LockScreen-1.workaround>

	private:
		//<CuteHMI.LockScreen-1.workaround target="Qt" cause="design">
		void setIdle(double idle);
		//</CuteHMI.LockScreen-1.workaround>

	private:
		struct Members
		{
			//<CuteHMI.LockScreen-1.workaround target="Qt" cause="design">
			int notifyEventCtr;
			double idle;	///< Idle time [seconds].
			bool idleMeasureEnabled;
			QTimer updateTimer;
			QTime idleTime;
			//</CuteHMI.LockScreen-1.workaround>

			Members();
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
