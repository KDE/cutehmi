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
