#include "version.hpp"

#include <base/CuteHMI.hpp>
#include <base/ProjectModel.hpp>
#include <base/ErrorInfo.hpp>
#include <base/PluginLoader.hpp>

#include <app/CuteApp.hpp>

//<workaround id="App-4" target="Qt" cause="bug">
#include <QApplication>
// Instead of:
//#include <QGuiApplication>
//</workaround>

#include <QQmlApplicationEngine>
#include <QIcon>
#include <QDir>
#include <QtDebug>
#include <QCommandLineParser>
#include <QQmlContext>
#include <QUrl>
#include <QCursor>
#include <QTranslator>
#include <QLibraryInfo>
#include <QFile>

int main(int argc, char * argv[])
{
	static const char * PLUGINS_SUBDIR = "plugins";

	QCoreApplication::setOrganizationDomain("cutehmi");
	QCoreApplication::setApplicationName("CuteHMI");
	QCoreApplication::setApplicationVersion(CUTEHMI_APP_VERSION);

	if (qgetenv("QT_IM_MODULE").isEmpty())
		qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
	qDebug() << "Input method: " << qgetenv("QT_IM_MODULE");

	if (qgetenv("QT_IM_MODULE") == "qtvirtualkeyboard") {
		if (qgetenv("QT_VIRTUALKEYBOARD_LAYOUT_PATH").isEmpty())
			qputenv("QT_VIRTUALKEYBOARD_LAYOUT_PATH", QByteArray(QDir("../layouts").absolutePath().toLocal8Bit()));
		qDebug() << "Qt Virtual Keyboard layouts path: " << qgetenv("QT_VIRTUALKEYBOARD_LAYOUT_PATH");
	}

//<principle id="Qt.Qt_5_7_0_Reference_Documentation.Threads_and_QObjects.QObject_Reentrancy.creating_QObjects_before_QApplication">
// "In general, creating QObjects before the QApplication is not supported and can lead to weird crashes on exit, depending on the
//	platform. This means static instances of QObject are also not supported. A properly structured single or multi-threaded application
//	should make the QApplication be the first created, and last destroyed QObject."

	//<workaround id="App-4" target="Qt" cause="bug">
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	cutehmi::app::CuteApp app(argc, argv);
	// Instead of:
//	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//	QGuiApplication app(argc, argv);
	//<workaround>
	app.setWindowIcon(QIcon(":/img/icon.png"));

	QCommandLineParser cmd;
	cmd.setApplicationDescription("CuteHMI");
	cmd.addHelpOption();
	cmd.addVersionOption();
	QCommandLineOption fullScreenOption({"f", "fullscreen"}, QCoreApplication::translate("main", "Run application in full screen mode."));
	cmd.addOption(fullScreenOption);
	QCommandLineOption projectOption({"p", "project"}, QCoreApplication::translate("main", "Load CuteHMI project <file>."), QCoreApplication::translate("main", "file"));
	cmd.addOption(projectOption);
	QCommandLineOption hideCursorOption({"t", "touch"}, QCoreApplication::translate("main", "Touch screen (hides mouse cursor)."));
	cmd.addOption(hideCursorOption);
	QCommandLineOption styleOption("qstyle", QCoreApplication::translate("main", "Set Qt Quick <style>."), QCoreApplication::translate("main", "style"));
	cmd.addOption(styleOption);
	QCommandLineOption langOption("lang", QCoreApplication::translate("main", "Choose application <language>."), QCoreApplication::translate("main", "language"));
	cmd.addOption(langOption);
	QCommandLineOption basedirOption("basedir", QCoreApplication::translate("main", "Set base directory to <dir>."), QCoreApplication::translate("main", "dir"));
	cmd.addOption(basedirOption);
	cmd.process(app);

	qDebug() << "Default locale: " << QLocale();

	QTranslator qtTranslator;
	if (cmd.isSet(langOption))
		qtTranslator.load("qt_" + cmd.value(langOption), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	else
		qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	app.installTranslator(& qtTranslator);

	if (cmd.isSet(styleOption)) {
		qputenv("QT_QUICK_CONTROLS_STYLE", cmd.value(styleOption).toLocal8Bit());
		qDebug() << "Qt Quick style: " << cmd.value(styleOption);
	}

	if (cmd.isSet(hideCursorOption))
		QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
	//<workaround id="App-5" target="Qt" cause="bug">
	// When run on raw Xorg server application does not show up cursor unless some controls are hovered.
	else
		QGuiApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
	//</workaround>

	QDir baseDir(QCoreApplication::applicationDirPath());
	if (cmd.isSet(basedirOption))
		baseDir = cmd.value(basedirOption);
	QString baseDirPath = baseDir.absolutePath() + "/";
	qDebug() << "Base directory: " << baseDirPath;

	cutehmi::base::CuteHMI & cuteHMI = cutehmi::base::CuteHMI::Instance();
	QDir dir(qApp->applicationDirPath());
	dir.cd(PLUGINS_SUBDIR);
	cuteHMI.project()->pluginLoader()->setPluginsDir(dir.canonicalPath());
	qDebug() << "Library paths: " << QCoreApplication::libraryPaths();

	// QQmlApplicationEngine scope. It's quite important to destroy "engine" before cutehmi::base::CuteHMI::Instance() members, because they
	// may still be used by some QML components (for example in "Component.onDestroyed" handlers).
	int result;
	{
		std::unique_ptr<QQmlApplicationEngine> engine(new QQmlApplicationEngine);
		engine->addImportPath("../CuteHMI/QML");
		engine->addImportPath("../QML");
		qDebug() << "QML import paths: " << engine->importPathList();
		engine->rootContext()->setContextProperty("cutehmi_app_mainScreenURL", "qrc:/qml/DefaultScreen.qml");
		engine->load(QUrl(QStringLiteral("qrc:/qml/MainWindow.qml")));

		if (!cmd.value(projectOption).isNull()) {
			cuteHMI.project()->loadXMLFile(baseDirPath + cmd.value(projectOption), engine->rootContext());

			cutehmi::base::ProjectNode * appNode = cuteHMI.project()->model()->root().child("cutehmi_app_1");
			if (appNode) {
				QString source;
				appNode->invoke("cutehmi::app::plugin::MainScreen", "source", Q_RETURN_ARG(QString, source));
				QUrl sourceUrl(source);
				if (sourceUrl.isValid()) {
					// Assure that URL is not mixing relative path with explicitly specified scheme, which is forbidden. QUrl::isValid() doesn't check this out.
					if (!sourceUrl.scheme().isEmpty() && QDir::isRelativePath(sourceUrl.path()))
						cutehmi::base::Prompt::Critical(QObject::tr("URL '%1' contains relative path along with URL scheme, which is forbidden.").arg(sourceUrl.url()));
					else {
						// If source URL is relative (does not contain scheme), then make absolute URL: file:///baseDirPath/sourceUrl.
						if (sourceUrl.isRelative())
							sourceUrl = QUrl::fromLocalFile(baseDirPath).resolved(sourceUrl);
						// Check if file exists and eventually set context property.
						if (sourceUrl.isLocalFile() && !QFile::exists(sourceUrl.toLocalFile()))
							cutehmi::base::Prompt::Critical(QObject::tr("Main screen file '%1' does not exist.").arg(sourceUrl.url()));
						else
							engine->rootContext()->setContextProperty("cutehmi_app_mainScreenURL", sourceUrl.url());
					}
				} else
					cutehmi::base::Prompt::Critical(QObject::tr("Invalid format of main screen URL '%1'.").arg(source));
			}
		}
		result = app.exec();
	}
	cutehmi::base::CuteHMI::Destroy();

	if (cmd.isSet(hideCursorOption))
		QGuiApplication::restoreOverrideCursor();
	//<workaround ref="App-5">
	else
		QGuiApplication::restoreOverrideCursor();
	//</workaround>

	return result;
//</principle>
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
