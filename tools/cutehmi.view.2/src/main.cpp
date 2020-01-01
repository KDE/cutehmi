#include "../cutehmi.metadata.hpp"
#include "../cutehmi.dirs.hpp"
#include "cutehmi/view/logging.hpp"

#include <cutehmi/ErrorInfo.hpp>
#include <cutehmi/Message.hpp>
#include <cutehmi/Messenger.hpp>
#include <cutehmi/Singleton.hpp>

#include <cutehmi/app/CuteApp.hpp>

//<cutehmi.view.2-4.workaround target="Qt" cause="bug">
#include <QApplication>
// Instead of:
//  #include <QGuiApplication>
//</cutehmi.view.2-4.workaround>

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
#include <QJsonDocument>
#include <QJsonObject>

using namespace cutehmi::view;

/**
 * Main function.
 * @param argc number of arguments passed to the program.
 * @param argv list of arguments passed to the program.
 * @return return code.
 */
int main(int argc, char * argv[])
{
	QCoreApplication::setOrganizationName(CUTEHMI_VIEW_VENDOR);
	QCoreApplication::setOrganizationDomain(CUTEHMI_VIEW_DOMAIN);
	QCoreApplication::setApplicationName(CUTEHMI_VIEW_FRIENDLY_NAME);
	QCoreApplication::setApplicationVersion(QString("%1.%2.%3").arg(CUTEHMI_VIEW_MAJOR).arg(CUTEHMI_VIEW_MINOR).arg(CUTEHMI_VIEW_MICRO));

	try {

		if (qgetenv("QT_IM_MODULE").isEmpty())
			qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
		CUTEHMI_DEBUG("Input method: " << qgetenv("QT_IM_MODULE"));

		if (qgetenv("QT_IM_MODULE") == "qtvirtualkeyboard") {
			if (qgetenv("QT_VIRTUALKEYBOARD_LAYOUT_PATH").isEmpty())
				qputenv("QT_VIRTUALKEYBOARD_LAYOUT_PATH", QByteArray(QDir("../layouts").absolutePath().toLocal8Bit()));
			CUTEHMI_DEBUG("Qt Virtual Keyboard layouts path: " << qgetenv("QT_VIRTUALKEYBOARD_LAYOUT_PATH"));
		}

		//<Qt-Qt_5_7_0_Reference_Documentation-Threads_and_QObjects-QObject_Reentrancy-creating_QObjects_before_QApplication.assumption>
		// "In general, creating QObjects before the QApplication is not supported and can lead to weird crashes on exit, depending on the
		//	platform. This means static instances of QObject are also not supported. A properly structured single or multi-threaded application
		//	should make the QApplication be the first created, and last destroyed QObject."

		//<cutehmi.view.2-4.workaround target="Qt" cause="bug">
		QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
		cutehmi::app::CuteApp app(argc, argv);
		// Instead of:
		//	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
		//	QGuiApplication app(argc, argv);
		//</cutehmi.view.2-4.workaround>
		app.setWindowIcon(QIcon(":/img/icon.png"));

		QJsonDocument metadataJson;
		{
			QFile metadataFile(":/" CUTEHMI_VIEW_NAME "/cutehmi.metadata.json");
			if (metadataFile.open(QFile::ReadOnly)) {
				metadataJson = QJsonDocument::fromJson(metadataFile.readAll());
			} else
				qFatal("Could not open ':/" CUTEHMI_VIEW_NAME "/cutehmi.metadata.json' file.");
		}

		QCommandLineParser cmd;
		cmd.setApplicationDescription(QCoreApplication::applicationName() + "\n" + metadataJson.object().value("description").toString());
		cmd.addHelpOption();
		cmd.addVersionOption();
		QCommandLineOption fullScreenOption({"f", "fullscreen"}, QCoreApplication::translate("main", "Run application in full screen mode."));
		cmd.addOption(fullScreenOption);
		QCommandLineOption initOption("init", QCoreApplication::translate("main", "Specify <initial> QML file to load."), QCoreApplication::translate("main", "initial"), "qrc:/qml/ExtensionLoader.qml");
		cmd.addOption(initOption);
		QCommandLineOption extensionOption("extension", QCoreApplication::translate("main", "Load extension specified by QML <import>."), QCoreApplication::translate("main", "import"));
		cmd.addOption(extensionOption);
		QCommandLineOption componentOption("component", QCoreApplication::translate("main", "Use <name> to specify extension QML component."), QCoreApplication::translate("main", "name"), "Main");
		cmd.addOption(componentOption);
		QCommandLineOption hideCursorOption({"t", "touch"}, QCoreApplication::translate("main", "Touch screen (hides mouse cursor)."));
		cmd.addOption(hideCursorOption);
		QCommandLineOption styleOption("qstyle", QCoreApplication::translate("main", "Set Qt Quick <style>."), QCoreApplication::translate("main", "style"));
		cmd.addOption(styleOption);
		QCommandLineOption langOption("lang", QCoreApplication::translate("main", "Choose application <language>."), QCoreApplication::translate("main", "language"));
		cmd.addOption(langOption);
		QCommandLineOption basedirOption("basedir", QCoreApplication::translate("main", "Set base directory to <dir>."), QCoreApplication::translate("main", "dir"));
		cmd.addOption(basedirOption);
		cmd.process(app);

		CUTEHMI_DEBUG("Default locale: " << QLocale());

		QTranslator qtTranslator;
		if (cmd.isSet(langOption))
			qtTranslator.load("qt_" + cmd.value(langOption), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
		else
			qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
		app.installTranslator(& qtTranslator);

		if (cmd.isSet(styleOption)) {
			qputenv("QT_QUICK_CONTROLS_STYLE", cmd.value(styleOption).toLocal8Bit());
			CUTEHMI_DEBUG("Qt Quick style: " << cmd.value(styleOption));
		}

		if (cmd.isSet(hideCursorOption))
			QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
		//<cutehmi.view.2-5.workaround target="Qt" cause="bug">
		// When run on raw Xorg server application does not show up cursor unless some controls are hovered.
		//<cutehmi.view.2-6.workaround target="Qt" cause="bug">
		// On Windows cursor does not refresh properly when using QGuiApplication::setOverrideCursor().
#ifndef Q_OS_WIN
		else
			QGuiApplication::setOverrideCursor(QCursor(Qt::ArrowCursor));
#endif
		//</cutehmi.view.2-6.workaround>
		//</cutehmi.view.2-5.workaround>

		QDir baseDir(QCoreApplication::applicationDirPath() + "/..");
		if (cmd.isSet(basedirOption))
			baseDir.setPath(cmd.value(basedirOption));
		QString baseDirPath = baseDir.absolutePath() + "/";
		CUTEHMI_DEBUG("Base directory: " << baseDirPath);

		CUTEHMI_DEBUG("Library paths: " << QCoreApplication::libraryPaths());

		std::unique_ptr<QQmlApplicationEngine> engine(new QQmlApplicationEngine);
		engine->addImportPath(baseDirPath + CUTEHMI_DIRS_EXTENSION_INSTALL_SUBDIR);

		CUTEHMI_DEBUG("QML import paths: " << engine->importPathList());

		QStringList extensionNameParts = cmd.value(extensionOption).split('.');
		QString extensionMajor;
		if (!extensionNameParts.isEmpty()) {
			bool hasExtensionMajor;
			extensionNameParts.last().toInt(& hasExtensionMajor);
			if (hasExtensionMajor)
				extensionMajor = extensionNameParts.takeLast();
		}
		QString extensionBasename = extensionNameParts.join('.');
		engine->rootContext()->setContextProperty("cutehmi_view_extensionBasename", extensionBasename);
		engine->rootContext()->setContextProperty("cutehmi_view_extensionMajor", extensionMajor);
		engine->rootContext()->setContextProperty("cutehmi_view_extensionComponent", cmd.value(componentOption));
		engine->rootContext()->setContextProperty("cutehmi_view_initURL", "qrc:/qml/DefaultScreen.qml");

		engine->load(QUrl(QStringLiteral("qrc:/qml/MainWindow.qml")));

		if (!cmd.value(initOption).isNull()) {
			CUTEHMI_DEBUG("Init: '" << cmd.value(initOption) << "'");
			CUTEHMI_DEBUG("Component: '" << cmd.value(componentOption) << "'");
			CUTEHMI_DEBUG("Extension: '" << cmd.value(extensionOption) << "'");
			QUrl initUrl(cmd.value(initOption));
			if (initUrl.isValid()) {
				// Assure that URL is not mixing relative path with explicitly specified scheme, which is forbidden. QUrl::isValid() doesn't check this out.
				if (!initUrl.scheme().isEmpty() && QDir::isRelativePath(initUrl.path()))
					cutehmi::Message::Critical(QObject::tr("URL '%1' contains relative path along with URL scheme, which is forbidden.").arg(initUrl.url()));
				else {
					// If source URL is relative (does not contain scheme), then make absolute URL: file:///baseDirPath/sourceUrl.
					if (initUrl.isRelative())
						initUrl = QUrl::fromLocalFile(baseDirPath).resolved(initUrl);
					// Check if file exists and eventually set context property.
					if (initUrl.isLocalFile() && !QFile::exists(initUrl.toLocalFile()))
						cutehmi::Message::Critical(QObject::tr("QML file '%1' does not exist.").arg(initUrl.url()));
					else
						engine->rootContext()->setContextProperty("cutehmi_view_initURL", initUrl.url());
				}
			} else
				cutehmi::Message::Critical(QObject::tr("Invalid format of QML file URL '%1'.").arg(cmd.value(initOption)));
		}

		//<Qt-Qt_5_9_1_Reference_Documentation-Qt_Core-C++_Classes-QCoreApplication-exec.assumption>
		// "We recommend that you connect clean-up code to the aboutToQuit() signal, instead of putting it in your application's main() function because on some
		//  platforms the exec() call may not return. For example, on Windows when the user logs off, the system terminates the process after Qt closes all top-level
		//  windows. Hence, there is no guarantee that the application will have time to exit its event loop and execute code at the end of the main() function after
		//  the exec() call."
		QObject::connect(& app, & cutehmi::app::CuteApp::aboutToQuit, [&]() {
			// It's quite important to destroy "engine" before cutehmi::CuteHMI::Instance() members, because they
			// may still be used by some QML components (for example in "Component.onDestroyed" handlers).
			engine.reset();

			cutehmi::destroySingletonInstances();

			if (cmd.isSet(hideCursorOption))
				QGuiApplication::restoreOverrideCursor();
			//<cutehmi.view.2-5.workaround>
			//<cutehmi.view.2-6.workaround target="Qt" cause="bug">
			// On Windows cursor does not refresh properly when using QGuiApplication::setOverrideCursor().
#ifndef Q_OS_WIN
			else
				QGuiApplication::restoreOverrideCursor();
#endif
			//</cutehmi.view.2-6.workaround>
			//</cutehmi.view.2-5.workaround>
		});

		return app.exec();

		//</Qt-Qt_5_9_1_Reference_Documentation-Qt_Core-C++_Classes-QCoreApplication-exec.assumption>

	} catch (const cutehmi::Messenger::NoAdvertiserException & e) {
		CUTEHMI_CRITICAL("Dialog message: " << e.message()->text());
		if (!e.message()->informativeText().isEmpty())
			CUTEHMI_CRITICAL("Informative text: " << e.message()->informativeText());
		if (!e.message()->detailedText().isEmpty())
			CUTEHMI_CRITICAL("Detailed text: " << e.message()->detailedText());
		CUTEHMI_CRITICAL("Available buttons: " << e.message()->buttons());
	} catch (const QException & e) {
		CUTEHMI_CRITICAL(e.what());
	} catch (const std::exception & e) {
		CUTEHMI_CRITICAL(e.what());
	} catch (...) {
		CUTEHMI_CRITICAL("Caught unrecognized exception.");
		throw;
	}

	return  EXIT_FAILURE;

	//</Qt-Qt_5_7_0_Reference_Documentation-Threads_and_QObjects-QObject_Reentrancy-creating_QObjects_before_QApplication.assumption>
}

//(c)C: Copyright © 2018-2019, Michał Policht <michal@policht.pl>, Wojtek Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
