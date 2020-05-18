#ifndef H_EXTENSIONS_CUTEHMI_GUI_0_INCLUDE_CUTEHMI_GUI_CUTEAPPLICATION_HPP
#define H_EXTENSIONS_CUTEHMI_GUI_0_INCLUDE_CUTEHMI_GUI_CUTEAPPLICATION_HPP

#include "internal/common.hpp"

#include <QApplication>
#include <QElapsedTimer>
#include <QTimer>

namespace cutehmi {
namespace gui {

/**
 * %Application.
 *
 * This class extends QApplication to provide idle measurment.
 */
class CUTEHMI_GUI_API CuteApplication:
//<CuteHMI.GUI-1.workaround target="Qt" cause="bug">
	public QApplication
// Instead of:
// public QGuiApplication
//</CuteHMI.GUI-1.workaround>
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

		CuteApplication(int & argc, char ** argv);

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
			QElapsedTimer idleTime;
			//</CuteHMI.LockScreen-1.workaround>

			Members():
				notifyEventCtr(0),
				idle(0.0),
				idleMeasureEnabled(false)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
