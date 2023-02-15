#include "CuteApplication.hpp"

namespace cutehmi {
namespace gui {

CuteApplication::CuteApplication(int & argc, char ** argv):
	Parent(argc, argv),
	m(new Members)
{
	m->updateTimer.setTimerType(Qt::VeryCoarseTimer);
	connect(& m->updateTimer, & QTimer::timeout, this, & CuteApplication::updateIdleTime);
}

CuteApplication * CuteApplication::create(QQmlEngine * qmlEngine, QJSEngine * jsEngine)
{
	Q_UNUSED(jsEngine)

	QObject * instance = cutehmi::gui::CuteApplication::instance();
	qmlEngine->setObjectOwnership(instance, QQmlEngine::CppOwnership);

	return qobject_cast<CuteApplication *>(instance);
}

double CuteApplication::idle() const
{
	return m->idle;
}

bool CuteApplication::idleMeasureEnabled() const
{
	return m->idleMeasureEnabled;
}

void CuteApplication::setIdleMeasureEnabled(bool idleEnabled)
{
	if (m->idleMeasureEnabled != idleEnabled) {
		m->idleMeasureEnabled = idleEnabled;
		if (idleEnabled) {
			m->notifyEventCtr = 0;
			setIdle(0.0);
			m->idleTime.start();
			m->updateTimer.start(IDLE_MEASURE_INTERVAL);
		} else {
			setIdle(0.0);
			m->updateTimer.stop();
		}
		emit idleMeasureEnabledChanged();
	}
}

bool CuteApplication::notify(QObject * receiver, QEvent * event)
{
	if (event->spontaneous())
		m->notifyEventCtr++;
	return Parent::notify(receiver, event);
}

void CuteApplication::updateIdleTime()
{
	if (m->notifyEventCtr) {
		setIdle(0.0);
		m->notifyEventCtr = 0;
	} else
		setIdle(idle() + static_cast<double>(m->idleTime.elapsed()) / 1000.0);
	m->idleTime.restart();
}

void CuteApplication::setIdle(double idle)
{
	if (m->idle != idle) {
		m->idle = idle;
		emit idleChanged();
	}
}

}
}

//(c)C: Copyright © 2020-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
