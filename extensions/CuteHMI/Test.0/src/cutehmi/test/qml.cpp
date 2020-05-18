#include <cutehmi/test/qml.hpp>

#include "../../../cutehmi.dirs.hpp"

#include <QQmlEngine>
#include <QQmlContext>
#include <QDir>
#include <QtTest/QtTest>

namespace cutehmi {
namespace test {

void setupScreenshotDirs(const char * projectRelativePath, QQmlEngine * engine)
{
	QString screenshotsDir = qEnvironmentVariable("CUTEHMI_INSTALL_DIR");
	if (screenshotsDir.isEmpty())
		screenshotsDir = QDir::temp().path();
	if (strlen(CUTEHMI_DIRS_ARTIFACTS_INSTALL_SUBDIR))
		screenshotsDir += "/" CUTEHMI_DIRS_ARTIFACTS_INSTALL_SUBDIR;
	screenshotsDir += QString("/screenshots/") + projectRelativePath + "/..";

	QString docScreenshotsDir = screenshotsDir + "/doc";

	QVERIFY(QDir().mkpath(screenshotsDir));
	QVERIFY(QDir().mkpath(docScreenshotsDir));

	engine->rootContext()->setContextProperty("screenshotsDir", screenshotsDir);
	engine->rootContext()->setContextProperty("docScreenshotsDir", docScreenshotsDir);
}


}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
