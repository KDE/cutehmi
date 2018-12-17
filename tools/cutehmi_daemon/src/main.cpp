#include "../cutehmi.metadata.hpp"
#include "../cutehmi.dirs.hpp"
#include "cutehmi/daemon/logging.hpp"
#include "cutehmi/daemon/Daemon.hpp"
#include "cutehmi/daemon/EngineThread.hpp"

#include <cutehmi/CuteHMI.hpp>
//#include <cutehmi/ProjectModel.hpp>
#include <cutehmi/ErrorInfo.hpp>

#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include <QtDebug>
#include <QCommandLineParser>
#include <QQmlContext>
#include <QUrl>
//#include <QCursor>
#include <QTranslator>
#include <QLibraryInfo>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtGlobal>

using namespace cutehmi::daemon;

/**
 * Main function.
 * @param argc number of arguments passed to the program.
 * @param argv list of arguments passed to the program.
 * @return return code.
 */
int main(int argc, char * argv[])
{
	try {
		QCoreApplication::setOrganizationDomain(QString(CUTEHMI_DAEMON_VENDOR).toLower());
		QCoreApplication::setApplicationName(CUTEHMI_DAEMON_VENDOR " " CUTEHMI_DAEMON_FRIENDLY_NAME);
		QCoreApplication::setApplicationVersion(QString("%1.%2.%3").arg(CUTEHMI_DAEMON_MAJOR).arg(CUTEHMI_DAEMON_MINOR).arg(CUTEHMI_DAEMON_MICRO));

		//<principle id="Qt-Qt_5_7_0_Reference_Documentation-Threads_and_QObjects-QObject_Reentrancy-creating_QObjects_before_QApplication">
		// "In general, creating QObjects before the QApplication is not supported and can lead to weird crashes on exit, depending on the
		//	platform. This means static instances of QObject are also not supported. A properly structured single or multi-threaded application
		//	should make the QApplication be the first created, and last destroyed QObject."

		//<workaround id="cutehmi_view-4" target="Qt" cause="bug">
		QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
		QCoreApplication app(argc, argv);
		// Instead of:
		//	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
		//	QGuiApplication app(argc, argv);
		//<workaround>
	//	app.setWindowIcon(QIcon(":/img/icon.png"));

		QJsonDocument metadataJson;
		{
			QFile metadataFile(":/cutehmi.metadata.json");
			if (metadataFile.open(QFile::ReadOnly)) {
				metadataJson = QJsonDocument::fromJson(metadataFile.readAll());
			} else
				CUTEHMI_DIE("Could not open ':/cutehmi.metadata.json' file.");
		}

		QCommandLineParser cmd;
		cmd.setApplicationDescription(QCoreApplication::applicationName() + "\n" + metadataJson.object().value("description").toString());
		cmd.addHelpOption();
		cmd.addVersionOption();
		QCommandLineOption projectOption({"p", "project"}, QCoreApplication::translate("main", "Load QML project <URL>."), QCoreApplication::translate("main", "URL"));
		cmd.addOption(projectOption);
		QCommandLineOption appOption("app", QCoreApplication::translate("main", "Run project in application mode."));
		cmd.addOption(appOption);
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

		QDir baseDir(QCoreApplication::applicationDirPath() + "/..");
		if (cmd.isSet(basedirOption))
			baseDir = cmd.value(basedirOption);
		QString baseDirPath = baseDir.absolutePath() + "/";
		CUTEHMI_DEBUG("Base directory: " << baseDirPath);

		CUTEHMI_DEBUG("Library paths: " << QCoreApplication::libraryPaths());

		EngineThread engineThread;
		std::unique_ptr<QQmlApplicationEngine> engine(new QQmlApplicationEngine);
		engine->addImportPath(baseDirPath + CUTEHMI_DIRS_QML_EXTENSION_INSTALL_DIRNAME);
		CUTEHMI_DEBUG("QML import paths: " << engine->importPathList());

		if (!cmd.value(projectOption).isNull()) {
			CUTEHMI_DEBUG("Project:" << cmd.value(projectOption));
			QUrl projectUrl(cmd.value(projectOption));
			if (projectUrl.isValid()) {
				// Assure that URL is not mixing relative path with explicitly specified scheme, which is forbidden. QUrl::isValid() doesn't check this out.
				if (!projectUrl.scheme().isEmpty() && QDir::isRelativePath(projectUrl.path()))
					cutehmi::CuteHMI::Instance().popupBridge()->critical(QObject::tr("URL '%1' contains relative path along with URL scheme, which is forbidden.").arg(projectUrl.url()));
				else {
					// If source URL is relative (does not contain scheme), then make absolute URL: file:///baseDirPath/sourceUrl.
					if (projectUrl.isRelative())
						projectUrl = QUrl::fromLocalFile(baseDirPath).resolved(projectUrl);
					// Check if file exists and eventually set context property.
					if (projectUrl.isLocalFile() && !QFile::exists(projectUrl.toLocalFile()))
						cutehmi::CuteHMI::Instance().popupBridge()->critical(QObject::tr("Project file '%1' does not exist.").arg(projectUrl.url()));
					else {
						engine->moveToThread(& engineThread);
						QObject::connect(& engineThread, SIGNAL(triggerLoad(const QString &)), engine.get(), SLOT(load(const QString &)));
						QObject::connect(& engineThread, SIGNAL(triggerLoad(const QString &)), & engineThread, SLOT(start()));
						QObject::connect(& app, & QCoreApplication::aboutToQuit, & engineThread, & QThread::quit);
						// Delegate management of engine to EngineThread, so that it gets deleted after thread finishes execution.
						QObject::connect(& engineThread, & QThread::finished, engine.release(), & QObject::deleteLater);

						emit engineThread.triggerLoad(projectUrl.url());
						int result = app.exec();
						engineThread.wait();
						return result;
					}
				}
			} else
				cutehmi::CuteHMI::Instance().popupBridge()->critical(QObject::tr("Invalid format of project URL '%1'.").arg(cmd.value(projectOption)));
		}
		//</principle>

		return EXIT_SUCCESS;

	} catch (const cutehmi::PopupBridge::NoAdvertiserException & e) {
		CUTEHMI_CRITICAL("Prompt message: " << e.prompt()->text());
		if (!e.prompt()->informativeText().isEmpty())
			CUTEHMI_CRITICAL("Informative text: " << e.prompt()->informativeText());
		if (!e.prompt()->detailedText().isEmpty())
			CUTEHMI_CRITICAL("Detailed text: " << e.prompt()->detailedText());
		CUTEHMI_CRITICAL("Available buttons: " << e.prompt()->buttons());
	} catch (const std::exception & e) {
		CUTEHMI_CRITICAL(e.what());
	} catch (...) {
		CUTEHMI_CRITICAL("Caught unrecognized exception.");
		throw;
	}

	return  EXIT_FAILURE;
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
