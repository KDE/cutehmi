#include "../cutehmi.metadata.hpp"
#include "../cutehmi.dirs.hpp"
#include "cutehmi/daemon/logging.hpp"
#include "cutehmi/daemon/Daemon.hpp"
#include "cutehmi/daemon/CoreData.hpp"
#include "cutehmi/daemon/Exception.hpp"

#include <cutehmi/Messenger.hpp>
#include <cutehmi/Singleton.hpp>

#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include <QCommandLineParser>
#include <QUrl>
#include <QTranslator>
#include <QLibraryInfo>
#include <QFile>
#include <QtGlobal>
#include <QQmlContext>

using namespace cutehmi::daemon;

/**
 * Main function.
 * @param argc number of arguments passed to the program.
 * @param argv list of arguments passed to the program.
 * @return return code.
 */
int main(int argc, char * argv[])
{
	//<cutehmi.daemon.2-silent_initialization.principle>
	// Output shall remain silent until daemon logging is set up.

	//<Qt-Qt_5_7_0_Reference_Documentation-Threads_and_QObjects-QObject_Reentrancy-creating_QObjects_before_QApplication.assumption>
	// "In general, creating QObjects before the QApplication is not supported and can lead to weird crashes on exit, depending on the
	//	platform. This means static instances of QObject are also not supported. A properly structured single or multi-threaded application
	//	should make the QApplication be the first created, and last destroyed QObject."

	// Set up application.

	QCoreApplication::setOrganizationName(CUTEHMI_DAEMON_VENDOR);
	QCoreApplication::setOrganizationDomain(CUTEHMI_DAEMON_DOMAIN);
	QCoreApplication::setApplicationName(CUTEHMI_DAEMON_FRIENDLY_NAME);
	QCoreApplication::setApplicationVersion(QString("%1.%2.%3").arg(CUTEHMI_DAEMON_MAJOR).arg(CUTEHMI_DAEMON_MINOR).arg(CUTEHMI_DAEMON_MICRO));

	QCoreApplication app(argc, argv);


	// Configure command line parser and process arguments.

	QCommandLineParser cmd;
	cmd.setApplicationDescription(CUTEHMI_DAEMON_TRANSLATED_FRIENDLY_NAME + "\n" + CUTEHMI_DAEMON_TRANSLATED_DESCRIPTION);
	cmd.addHelpOption();
	cmd.addVersionOption();
	CoreData::Options opt {
		QCommandLineOption("app", QCoreApplication::translate("main", "Run project in application mode.")),
		QCommandLineOption("basedir", QCoreApplication::translate("main", "Set base directory to <dir>."), QCoreApplication::translate("main", "dir")),
		QCommandLineOption("init", QCoreApplication::translate("main", "Override loader by specifying initial QML <file> to load."), QCoreApplication::translate("main", "file")),
		QCommandLineOption("extension", QCoreApplication::translate("main", "Load extension specified by QML <import>."), QCoreApplication::translate("main", "import")),
		QCommandLineOption("component", QCoreApplication::translate("main", "Extension component <name>."), QCoreApplication::translate("main", "name")),
		QCommandLineOption("lang", QCoreApplication::translate("main", "Choose application <language>."), QCoreApplication::translate("main", "language")),
		QCommandLineOption("pidfile", QCoreApplication::translate("main", "PID file <path> (Unix-specific)."), QCoreApplication::translate("main", "path"))
	};
#ifdef CUTEHMI_DAEMON_DEFAULT_INIT
	opt.init.setDefaultValue(CUTEHMI_DAEMON_DEFAULT_INIT);
#else
	opt.init.setDefaultValue("qrc:/qml/ExtensionLoader.qml");
#endif
#ifdef CUTEHMI_DAEMON_FORCE_DEFAULT_OPTIONS
	opt.init.setFlags(QCommandLineOption::HiddenFromHelp);
#endif
#ifdef CUTEHMI_DAEMON_DEFAULT_EXTENSION
	opt.extension.setDefaultValue(CUTEHMI_DAEMON_DEFAULT_EXTENSION);
#endif
#ifdef CUTEHMI_DAEMON_FORCE_DEFAULT_OPTIONS
	opt.extension.setFlags(QCommandLineOption::HiddenFromHelp);
#endif
#ifdef CUTEHMI_DAEMON_DEFAULT_COMPONENT
	opt.component.setDefaultValue(CUTEHMI_DAEMON_DEFAULT_COMPONENT);
#else
	opt.component.setDefaultValue("Main");
#endif
#ifdef CUTEHMI_DAEMON_FORCE_DEFAULT_OPTIONS
	opt.component.setFlags(QCommandLineOption::HiddenFromHelp);
#endif
	opt.pidfile.setDefaultValue(QString("/var/run/") + CUTEHMI_DAEMON_NAME ".pid");
	opt.pidfile.setDescription(opt.pidfile.description() + "\nDefault value: '" + opt.pidfile.defaultValues().at(0) + "'.");
	opt.basedir.setDefaultValue(QDir(QCoreApplication::applicationDirPath() + "/..").canonicalPath());
	opt.basedir.setDescription(opt.basedir.description() + "\nDefault value: '" + opt.basedir.defaultValues().at(0) + "'.");
	cmd.addOption(opt.app);
	cmd.addOption(opt.basedir);
	cmd.addOption(opt.init);
	cmd.addOption(opt.extension);
	cmd.addOption(opt.component);
	cmd.addOption(opt.lang);
	cmd.addOption(opt.pidfile);
	cmd.process(app);


	// Prepare program core.

	CoreData data;
	data.app = & app;
	data.cmd = & cmd;
	data.opt = & opt;

	std::function<int(CoreData &)> core = [](CoreData & data) {
		try {
			CUTEHMI_DEBUG("Default locale: " << QLocale());
			CUTEHMI_DEBUG("Language: " << data.cmd->value(data.opt->lang));

			QTranslator qtTranslator;
			if (data.cmd->isSet(data.opt->lang))
				qtTranslator.load("qt_" + data.cmd->value(data.opt->lang), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
			else
				qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
			data.app->installTranslator(& qtTranslator);

			QDir baseDir = data.cmd->value(data.opt->basedir);
			QString baseDirPath = baseDir.absolutePath() + "/";
			CUTEHMI_DEBUG("Base directory: " << baseDirPath);

			CUTEHMI_DEBUG("Library paths: " << QCoreApplication::libraryPaths());

			QQmlApplicationEngine engine;
			engine.addImportPath(baseDirPath + CUTEHMI_DIRS_EXTENSIONS_INSTALL_SUBDIR);
			CUTEHMI_DEBUG("QML import paths: " << engine.importPathList());

#ifndef CUTEHMI_DAEMON_FORCE_DEFAULT_OPTIONS
			QString extension = data.cmd->value(data.opt->extension);
			QString init = data.cmd->value(data.opt->init);
			QString component = data.cmd->value(data.opt->component);
#else
			QString extension = data.opt->extension.defaultValues().first();
			QString init = data.opt->init.defaultValues().first();
			QString component = data.opt->component.defaultValues().first();

			if (data.cmd->value(data.opt->extension) != extension)
				throw Exception(QCoreApplication::translate("main", "You can not use '%1' option, because 'forceDefaultOptions' option has been set during compilation time.").arg(data.opt->extension.names().join(", ")).toLocal8Bit().constData());
			if (data.cmd->value(data.opt->init) != init)
				throw Exception(QCoreApplication::translate("main", "You can not use '%1' option, because 'forceDefaultOptions' option has been set during compilation time.").arg(data.opt->init.names().join(", ")).toLocal8Bit().constData());
			if (data.cmd->value(data.opt->component) != component)
				throw Exception(QCoreApplication::translate("main", "You can not use '%1' option, because 'forceDefaultOptions' option has been set during compilation time.").arg(data.opt->component.names().join(", ")).toLocal8Bit().constData());
#endif

			QStringList extensionParts = extension.split('.');
			QString extensionMajor;
			if (!extensionParts.isEmpty()) {
				bool hasExtensionMajor;
				extensionParts.last().toInt(& hasExtensionMajor);
				if (hasExtensionMajor)
					extensionMajor = extensionParts.takeLast();
			}
			QString extensionBasename = extensionParts.join('.');
			engine.rootContext()->setContextProperty("cutehmi_daemon_extensionBasename", extensionBasename);
			engine.rootContext()->setContextProperty("cutehmi_daemon_extensionMajor", extensionMajor);
			engine.rootContext()->setContextProperty("cutehmi_daemon_extensionComponent", component);

			//<cutehmi.daemon.2-1.workaround target="Qt" cause="QTBUG-73649">
			// Class QQmlApplicationEngine connects Qt.quit() signal to QCoreApplication::quit() and QQmlApplicationEngine::exit()
			// signal to QCoreApplication::exit(), but it does so with AutoConnection. This causes in some circumstances problems,
			// which are described in Qt documentation (see QCoreApplication::exit()). Workaround is to disconnect signals and
			// connect them again with QueuedConnection.
			engine.disconnect(& engine, nullptr, data.app, nullptr);
			engine.connect(& engine, SIGNAL(quit()), data.app, SLOT(quit()), Qt::QueuedConnection);
			engine.connect(& engine, & QQmlApplicationEngine::exit, data.app, & QCoreApplication::exit, Qt::QueuedConnection);
			//</cutehmi.daemon.2-1.workaround>

			if (!init.isNull()) {
				CUTEHMI_DEBUG("Init: '" << init << "'");
				CUTEHMI_DEBUG("Component: '" << component << "'");
				CUTEHMI_DEBUG("Extension: '" << extension << "'");
				QUrl initUrl(init);
				if (initUrl.isValid()) {
					// Assure that URL is not mixing relative path with explicitly specified scheme, which is forbidden. QUrl::isValid() doesn't check this out.
					if (!initUrl.scheme().isEmpty() && QDir::isRelativePath(initUrl.path()))
						throw Exception(QCoreApplication::translate("main", "URL '%1' contains relative path along with URL scheme, which is forbidden.").arg(initUrl.url()));
					else {
						// If source URL is relative (does not contain scheme), then make absolute URL: file:///baseDirPath/sourceUrl.
						if (initUrl.isRelative())
							initUrl = QUrl::fromLocalFile(baseDirPath).resolved(initUrl);
						// Check if file exists and eventually set context property.
						if (initUrl.isLocalFile() && !QFile::exists(initUrl.toLocalFile()))
							throw Exception(QCoreApplication::translate("main", "QML file '%1' does not exist.").arg(initUrl.url()));
						else {
							engine.load(initUrl.url());
							int result = data.app->exec();
							engine.collectGarbage();
							return result;
						}
					}
				} else
					throw Exception(QCoreApplication::translate("main", "Invalid format of QML file URL '%1'.").arg(init));
			} else
				throw Exception(QCoreApplication::translate("main", "No initial loader has been specified."));

			return EXIT_SUCCESS;

		} catch (const Exception & e) {
			CUTEHMI_CRITICAL(e.what());
		} catch (const cutehmi::Messenger::NoAdvertiserException & e) {
			CUTEHMI_CRITICAL("Dialog message: " << e.message()->text());
			if (!e.message()->informativeText().isEmpty())
				CUTEHMI_CRITICAL("Informative text: " << e.message()->informativeText());
			if (!e.message()->detailedText().isEmpty())
				CUTEHMI_CRITICAL("Detailed text: " << e.message()->detailedText());
			CUTEHMI_CRITICAL("Available buttons: " << e.message()->buttons());
		} catch (const std::exception & e) {
			CUTEHMI_CRITICAL(e.what());
		} catch (...) {
			CUTEHMI_CRITICAL("Caught unrecognized exception.");
			throw;
		}

		return  EXIT_FAILURE;
	};


	// Run program core in daemon or application mode.

	int exitCode;

	if (!cmd.isSet(opt.app)) {
		Daemon daemon(& data, core);

		// At this point logging should be configured and printing facilities silenced. Not much to say anyways...
		//</cutehmi.daemon.2-silent_initialization.principle>

		exitCode = daemon.exitCode();
	} else
		exitCode = core(data);

	// Destroy singleton instances before QCoreApplication. Ignoring the recommendation to connect clean-up code to the
	// aboutToQuit() signal, because for daemon it is always violent termination if QCoreApplication::exec() does not exit.
	cutehmi::destroySingletonInstances();

	return exitCode;

	//</Qt-Qt_5_7_0_Reference_Documentation-Threads_and_QObjects-QObject_Reentrancy-creating_QObjects_before_QApplication.assumption>
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
