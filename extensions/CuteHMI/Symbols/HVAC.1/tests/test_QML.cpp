#include "cutehmi.dirs.hpp"

#include <cutehmi/test/qml.hpp>

#include <QtQuickTest>

class test_QML:
	public QObject
{
		Q_OBJECT

	public slots:
		void qmlEngineAvailable(QQmlEngine * engine)
		{
			cutehmi::test::setupScreenshotDirs(CUTEHMI_DIRS_PROJECT_RELATIVE_PATH, engine);
		}

		void cleanupTestCase()
		{
		}
};


QUICK_TEST_MAIN_WITH_SETUP(CuteHMI.Symbols.HVAC.0, test_QML)
#include "test_QML.moc"

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
