#ifndef H_EXTENSIONS_CUTEHMI_GUI_1_INCLUDE_CUTEHMI_GUI_CUTEAPPLICATION_HPP
#define H_EXTENSIONS_CUTEHMI_GUI_1_INCLUDE_CUTEHMI_GUI_CUTEAPPLICATION_HPP

#include "internal/common.hpp"

#include <QApplication>
#include <QElapsedTimer>
#include <QTimer>
#include <QQmlEngine>

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
		//<CuteHMI.Workarounds.Qt5Compatibility-4.workaround target="Qt" cause="Qt5.15-QML_SINGLETON">
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
		QML_NAMED_ELEMENT(CuteApplication)
		QML_UNCREATABLE("CuteApplication is a singleton")
		QML_SINGLETON
#endif
		//</CuteHMI.Workarounds.Qt5Compatibility-4.workaround>

	public:
		//<CuteHMI.LockScreen-1.workaround target="Qt" cause="design">
		static constexpr int IDLE_MEASURE_INTERVAL = 1000;	///< Idle measurement update interval [milliseconds].
		//</CuteHMI.LockScreen-1.workaround>

		//<CuteHMI.LockScreen-1.workaround target="Qt" cause="design">
		Q_PROPERTY(double idle READ idle NOTIFY idleChanged)

		Q_PROPERTY(bool idleMeasureEnabled READ idleMeasureEnabled WRITE setIdleMeasureEnabled NOTIFY idleMeasureEnabledChanged)
		//</CuteHMI.LockScreen-1.workaround>

		CuteApplication(int & argc, char ** argv);

		/**
		 * Create intance.
		 * @param qmlEngine QML engine instance.
		 * @param jsEngine JavaScript engine instance.
		 * @return instance.
		 *
		 * @note this method is used by QQmlEngine when class is annotated with QML_SINGLETON macro.
		 */
		static CuteApplication * create(QQmlEngine * qmlEngine, QJSEngine * jsEngine);

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
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
