#include "autogen/cutehmi.metadata.hpp"
#include "autogen/cutehmi.dirs.hpp"
#include "cutehmi/daemon/logging.hpp"
#include "cutehmi/daemon/Daemon.hpp"
#include "cutehmi/daemon/CoreData.hpp"
#include "cutehmi/daemon/Exception.hpp"

#include <cutehmi/Messenger.hpp>
#include <cutehmi/Singleton.hpp>
#include <cutehmi/Internationalizer.hpp>

#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include <QCommandLineParser>
#include <QUrl>
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
#ifdef CUTEHMI_DAEMON_DEFAULT_INIT
	static constexpr const char * DEFAULT_INIT = CUTEHMI_DAEMON_DEFAULT_INIT;
#else
	static constexpr const char * DEFAULT_INIT = "qrc:/qml/ExtensionLoader.qml";
#endif

#ifdef CUTEHMI_DAEMON_DEFAULT_EXTENSION
	static constexpr const char * DEFAULT_EXTENSION = CUTEHMI_DAEMON_DEFAULT_EXTENSION;
#else
	static constexpr const char * DEFAULT_EXTENSION = "";
#endif

#ifdef CUTEHMI_DAEMON_DEFAULT_COMPONENT
	static constexpr const char * DEFAULT_COMPONENT = CUTEHMI_DAEMON_DEFAULT_COMPONENT;
#else
	static constexpr const char * DEFAULT_COMPONENT = "Daemon";
#endif

#ifdef CUTEHMI_DAEMON_DEFAULT_MINOR
	static constexpr const char * DEFAULT_MINOR = CUTEHMI_DAEMON_DEFAULT_MINOR;
#else
	static constexpr const char * DEFAULT_MINOR = "0";
#endif

	static constexpr const char * DEFAULT_FORKS = "2";

	//<cutehmi.daemon-silent_initialization.principle>
	// Output shall remain silent until daemon logging is set up.

	//<Qt-Qt_5_7_0_Reference_Documentation-Threads_and_QObjects-QObject_Reentrancy-creating_QObjects_before_QApplication.assumption>
	// "In general, creating QObjects before the QApplication is not supported and can lead to weird crashes on exit, depending on the
	//	platform. This means static instances of QObject are also not supported. A properly structured single or multi-threaded application
	//	should make the QApplication be the first created, and last destroyed QObject."

	// Set up application.

	QCoreApplication::setOrganizationName(CUTEHMI_DAEMON_VENDOR);
	QCoreApplication::setOrganizationDomain(CUTEHMI_DAEMON_DOMAIN);
	QCoreApplication::setApplicationName(CUTEHMI_DAEMON_FRIENDLY_NAME);
	QCoreApplication::setApplicationVersion(CUTEHMI_DAEMON_VERSION);

	QCoreApplication app(argc, argv);


	// Initial language setup.

	QString language = QLocale::system().name();
#ifdef CUTEHMI_DAEMON_DEFAULT_LANGUAGE
	language = CUTEHMI_DAEMON_DEFAULT_LANGUAGE;
#endif
	if (!qEnvironmentVariableIsEmpty("CUTEHMI_LANGUAGE"))
		language = qgetenv("CUTEHMI_LANGUAGE");


	// Configure command line parser and process arguments.

	QCommandLineParser cmd;
	cmd.setApplicationDescription(CUTEHMI_DAEMON_TRANSLATED_FRIENDLY_NAME + "\n" + CUTEHMI_DAEMON_TRANSLATED_DESCRIPTION);
	cmd.addHelpOption();
	cmd.addVersionOption();
	CoreData::Options opt {
		QStringList({"extension", QCoreApplication::translate("main", "Extension to import."), "[extension]"}),
		QStringList({"component", QCoreApplication::translate("main", "Component to create. Defaults to '%1'.").arg(DEFAULT_COMPONENT), "[component]"}),
		QCommandLineOption("app", QCoreApplication::translate("main", "Run project in application mode.")),
		QCommandLineOption("basedir", QCoreApplication::translate("main", "Set base directory to <dir>."), QCoreApplication::translate("main", "dir")),
		QCommandLineOption("init", QCoreApplication::translate("main", "Override loader by specifying initial QML <file> to load."), QCoreApplication::translate("main", "file")),
		QCommandLineOption({"m", "minor"}, QCoreApplication::translate("main", "Use <version> for extension minor version to import."), QCoreApplication::translate("main", "version")),
		QCommandLineOption("lang", QCoreApplication::translate("main", "Choose application <language>."), QCoreApplication::translate("main", "language")),
		QCommandLineOption("pidfile", QCoreApplication::translate("main", "PID file <path> (Unix-specific)."), QCoreApplication::translate("main", "path")),
		QCommandLineOption("forks", QCoreApplication::translate("main", "Denotes <number> of forks the daemon should perform (Unix-specific)."), QCoreApplication::translate("main", "number")),
	};
	opt.init.setDefaultValue(DEFAULT_INIT);
	opt.minor.setDefaultValue(DEFAULT_MINOR);
	opt.lang.setDefaultValue(language);
	opt.pidfile.setDefaultValue(QString("/var/run/") + CUTEHMI_DAEMON_NAME ".pid");
	opt.pidfile.setDescription(opt.pidfile.description() + "\nDefault value: '" + opt.pidfile.defaultValues().at(0) + "'.");
	opt.basedir.setDefaultValue(QDir(QCoreApplication::applicationDirPath() + "/..").canonicalPath());
	opt.basedir.setDescription(opt.basedir.description() + "\nDefault value: '" + opt.basedir.defaultValues().at(0) + "'.");
	opt.forks.setDefaultValue(DEFAULT_FORKS);
	opt.forks.setDescription(opt.forks.description() + "\nDefault value: '" + opt.forks.defaultValues().at(0) + "'.");
	cmd.addOption(opt.app);
	cmd.addOption(opt.basedir);
	cmd.addOption(opt.init);
	cmd.addOption(opt.minor);
	cmd.addOption(opt.lang);
	cmd.addOption(opt.pidfile);
	cmd.addOption(opt.forks);
#ifdef CUTEHMI_DAEMON_FORCE_DEFAULT_OPTIONS
	opt.init.setFlags(QCommandLineOption::HiddenFromHelp);
	opt.minor.setFlags(QCommandLineOption::HiddenFromHelp);
#else
	cmd.addPositionalArgument(opt.extension.at(0), opt.extension.at(1), opt.extension.at(2));
	cmd.addPositionalArgument(opt.component.at(0), opt.component.at(1), opt.component.at(2));
#endif
	cmd.process(app);


	// Prepare program core.

	CoreData coreData;
	coreData.app = & app;
	coreData.cmd = & cmd;
	coreData.opt = & opt;
	coreData.language = language;

	std::function<int(CoreData &)> core = [](CoreData & data) {
		try {
			CUTEHMI_DEBUG("Default locale: " << QLocale());

			if (!qgetenv("CUTEHMI_LANGUAGE").isEmpty())
				CUTEHMI_DEBUG("Default language set by 'CUTEHMI_LANGUAGE' environmental variable: " << qgetenv("CUTEHMI_LANGUAGE"));

			if (data.cmd->isSet(data.opt->lang))
				data.language = data.cmd->value(data.opt->lang);

			CUTEHMI_DEBUG("Language: " << data.language);
			cutehmi::Internationalizer::Instance().setUILanguage(data.language);
			cutehmi::Internationalizer::Instance().loadQtTranslation();
			cutehmi::Internationalizer::Instance().loadTranslation(CUTEHMI_DAEMON_NAME);

			QDir baseDir = data.cmd->value(data.opt->basedir);
			QString baseDirPath = baseDir.absolutePath() + "/";
			CUTEHMI_DEBUG("Base directory: " << baseDirPath);

			QString extensionsDirPath = QDir::cleanPath(QCoreApplication::applicationDirPath() + "/" + QDir("/" CUTEHMI_DIRS_TOOLS_INSTALL_SUBDIR).relativeFilePath("/" CUTEHMI_DIRS_EXTENSIONS_INSTALL_SUBDIR));
			CUTEHMI_DEBUG("Extensions directory: " << extensionsDirPath);

			QCoreApplication::addLibraryPath(extensionsDirPath);
			CUTEHMI_DEBUG("Library paths: " << QCoreApplication::libraryPaths());

			QQmlApplicationEngine engine;
			engine.addImportPath(extensionsDirPath);
			CUTEHMI_DEBUG("QML import paths: " << engine.importPathList());

			QStringList positionalArguments = data.cmd->positionalArguments();
#ifndef CUTEHMI_DAEMON_FORCE_DEFAULT_OPTIONS
			QString extension;
			if (positionalArguments.length() > 0)
				extension = positionalArguments.at(0);
			else
				extension = DEFAULT_EXTENSION;

			QString extensionMinor = data.cmd->value(data.opt->minor);
			QString init = data.cmd->value(data.opt->init);
			QString component;
			if (positionalArguments.length() > 1)
				component = positionalArguments.at(1);
			else
				component = DEFAULT_COMPONENT;
#else
			QString extension = DEFAULT_EXTENSION;
			QString component = DEFAULT_COMPONENT;
			QString extensionMinor = data.opt->minor.defaultValues().first();
			QString init = data.opt->init.defaultValues().first();

			if (positionalArguments.length() > 1)
				throw Exception(QCoreApplication::translate("main", "You can not use 'component' option, because 'forceDefaultOptions' option has been set during compilation time.").toLocal8Bit().constData());
			if (positionalArguments.length() > 0)
				throw Exception(QCoreApplication::translate("main", "You can not use 'extension' option, because 'forceDefaultOptions' option has been set during compilation time.").toLocal8Bit().constData());
			if (data.cmd->value(data.opt->minor) != extensionMinor)
				throw Exception(QCoreApplication::translate("main", "You can not use '%1' option, because 'forceDefaultOptions' option has been set during compilation time.").arg(data.opt->minor.names().join(", ")).toLocal8Bit().constData());
			if (data.cmd->value(data.opt->init) != init)
				throw Exception(QCoreApplication::translate("main", "You can not use '%1' option, because 'forceDefaultOptions' option has been set during compilation time.").arg(data.opt->init.names().join(", ")).toLocal8Bit().constData());
#endif
			if (!extensionMinor.isEmpty()) {
				bool ok;
				extensionMinor.toUInt(& ok);
				if (!ok)
					throw Exception(QCoreApplication::translate("main", "Command line argument error: value of '%1' option must be a number.").arg(data.opt->minor.names().last()));
			}
			QString extensionBaseName = extension.left(extension.lastIndexOf('.'));
			QString extensionMajor = extension.right(extension.length() - extension.lastIndexOf('.') - 1);
			if (!extension.isEmpty()) {
				bool ok;
				extensionMajor.toUInt(& ok);
				if (!ok)
					throw Exception(QCoreApplication::translate("main", "Command line argument error: please specify extension with major version number after the last dot."));
			}
			engine.rootContext()->setContextProperty("cutehmi_daemon_extensionBaseName", extensionBaseName);
			engine.rootContext()->setContextProperty("cutehmi_daemon_extensionMajor", extensionMajor);
			engine.rootContext()->setContextProperty("cutehmi_daemon_extensionMinor", extensionMinor);
			engine.rootContext()->setContextProperty("cutehmi_daemon_extensionComponent", component);

			//<cutehmi.daemon-1.workaround target="Qt" cause="QTBUG-73649">
			// Class QQmlApplicationEngine connects Qt.quit() signal to QCoreApplication::quit() and QQmlApplicationEngine::exit()
			// signal to QCoreApplication::exit(), but it does so with AutoConnection. This causes in some circumstances problems,
			// which are described in Qt documentation (see QCoreApplication::exit()). Workaround is to disconnect signals and
			// connect them again with QueuedConnection.
			engine.disconnect(& engine, nullptr, data.app, nullptr);
			engine.connect(& engine, SIGNAL(quit()), data.app, SLOT(quit()), Qt::QueuedConnection);
			engine.connect(& engine, & QQmlApplicationEngine::exit, data.app, & QCoreApplication::exit, Qt::QueuedConnection);
			//</cutehmi.daemon-1.workaround>

			if (!init.isNull()) {
				CUTEHMI_DEBUG("Init: '" << init << "'");
				CUTEHMI_DEBUG("Extension: '" << extension << "'");
				CUTEHMI_DEBUG("Minor: '" << extensionMinor << "'");
				CUTEHMI_DEBUG("Component: '" << component << "'");
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
							// Load extension translation and connect uiLanguageChanged() signal to retranslate() slot.
							if (!extension.isEmpty())
								cutehmi::Internationalizer::Instance().loadTranslation(extension);
							QObject::connect(& cutehmi::Internationalizer::Instance(), & cutehmi::Internationalizer::uiLanguageChanged, & engine, & QQmlApplicationEngine::retranslate);

							engine.load(initUrl.url());
							int result = data.app->exec();

							engine.collectGarbage();
							cutehmi::Internationalizer::Instance().unloadTranslations();
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
		Daemon daemon(& coreData, core);

		// At this point logging should be configured and printing facilities silenced. Not much to say anyways...
		//</cutehmi.daemon-silent_initialization.principle>

		exitCode = daemon.exitCode();
	} else
		exitCode = core(coreData);

	// Destroy singleton instances before QCoreApplication. Ignoring the recommendation to connect clean-up code to the
	// aboutToQuit() signal, because for daemon it is always violent termination if QCoreApplication::exec() does not exit.
	cutehmi::destroySingletonInstances();

	return exitCode;

	//</Qt-Qt_5_7_0_Reference_Documentation-Threads_and_QObjects-QObject_Reentrancy-creating_QObjects_before_QApplication.assumption>
}

//(c)C: Copyright © 2020-2024, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
