#include "../cutehmi.metadata.hpp"
#include "../cutehmi.dirs.hpp"
#include "cutehmi/console/logging.hpp"
#include "cutehmi/console/Exception.hpp"
#include "cutehmi/console/Interpreter.hpp"
#include "cutehmi/console/InputHandler.hpp"

#include <cutehmi/Messenger.hpp>

#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include <QCommandLineParser>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include <QtGlobal>
#include <QThread>

using namespace cutehmi::console;

/**
 * Main function.
 * @param argc number of arguments passed to the program.
 * @param argv list of arguments passed to the program.
 * @return return code.
 */
int main(int argc, char * argv[])
{
	// Set up application.

	QCoreApplication::setOrganizationName(CUTEHMI_CONSOLE_VENDOR);
	QCoreApplication::setOrganizationDomain(CUTEHMI_CONSOLE_DOMAIN);
	QCoreApplication::setApplicationName(CUTEHMI_CONSOLE_FRIENDLY_NAME);
	QCoreApplication::setApplicationVersion(QString("%1.%2.%3").arg(CUTEHMI_CONSOLE_MAJOR).arg(CUTEHMI_CONSOLE_MINOR).arg(CUTEHMI_CONSOLE_MICRO));

	try {
		//<Qt-Qt_5_7_0_Reference_Documentation-Threads_and_QObjects-QObject_Reentrancy-creating_QObjects_before_QApplication.assumption>
		// "In general, creating QObjects before the QApplication is not supported and can lead to weird crashes on exit, depending on the
		//	platform. This means static instances of QObject are also not supported. A properly structured single or multi-threaded application
		//	should make the QApplication be the first created, and last destroyed QObject."

		QCoreApplication app(argc, argv);


		// Translations initial setup.

		QString language = QLocale::system().name();
#ifdef CUTEHMI_VIEW_DEFAULT_LANGUAGE
		language = CUTEHMI_VIEW_DEFAULT_LANGUAGE;
#endif
		if (!qgetenv("CUTEHMI_LANGUAGE").isEmpty()) {
			language = qgetenv("CUTEHMI_LANGUAGE");
			CUTEHMI_DEBUG("Language set by 'CUTEHMI_LANGUAGE' environmental variable: " << qgetenv("CUTEHMI_LANGUAGE"));
		}
		QTranslator qtTranslator;
		if (!qtTranslator.load("qt_" + language, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
			CUTEHMI_WARNING("Could not load translations file '" << "qt_" + language << "'.");
		app.installTranslator(& qtTranslator);

		QTranslator translator;
		QString translationsDir = QDir("/" CUTEHMI_DIRS_TOOLS_INSTALL_SUBDIR).relativeFilePath("/" CUTEHMI_DIRS_TRANSLATIONS_INSTALL_SUBDIR);
		QString translationFilePrefix = QString(CUTEHMI_CONSOLE_NAME).replace('.', '-') + "_";
		QString translationFile = translationFilePrefix + language;
		if (!translator.load(translationFile, translationsDir))
			CUTEHMI_WARNING("Could not load translations file '" << translationFile << "'.");
		app.installTranslator(& translator);


		// Configure command line parser and process arguments.

		QCommandLineParser cmd;
		cmd.setApplicationDescription(CUTEHMI_CONSOLE_TRANSLATED_FRIENDLY_NAME + "\n" + CUTEHMI_CONSOLE_TRANSLATED_DESCRIPTION);
		cmd.addHelpOption();
		cmd.addVersionOption();

		QCommandLineOption langOption("lang", QCoreApplication::translate("main", "Choose application <language>."), QCoreApplication::translate("main", "language"));
		langOption.setDefaultValue(language);
		cmd.addOption(langOption);

		QCommandLineOption basedirOption("basedir", QCoreApplication::translate("main", "Set base directory to <dir>."), QCoreApplication::translate("main", "dir"));
		cmd.addOption(basedirOption);

		QCommandLineOption componentOption("component", QCoreApplication::translate("main", "Extension component <name>."), QCoreApplication::translate("main", "name"));
		componentOption.setDefaultValue("Console");
		cmd.addOption(componentOption);

		QCommandLineOption minorOption({"m", "minor"}, QCoreApplication::translate("main", "Use <version> for extension minor version to import."), QCoreApplication::translate("main", "version"));
		minorOption.setDefaultValue("0");
		cmd.addOption(minorOption);

		cmd.addPositionalArgument("extension", QCoreApplication::translate("main", "Extension to import."), "[extension]");

		cmd.addPositionalArgument("component", QCoreApplication::translate("main", "Component to create."), "[component]");

		cmd.process(app);


		// Finalize setting up translations.

		CUTEHMI_DEBUG("Default locale: " << QLocale());
		CUTEHMI_DEBUG("Language: " << cmd.value(langOption));

		if (!qtTranslator.load("qt_" + cmd.value(langOption), QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
			CUTEHMI_WARNING("Could not load translations file '" << "qt_" + cmd.value(langOption) << "'.");

		translationFile = translationFilePrefix + cmd.value(langOption);
		if (!translator.load(translationFile, translationsDir))
			CUTEHMI_WARNING("Could not load translations file '" << translationFile << "'.");


		// Prepare QML engine.

		QDir baseDir(QCoreApplication::applicationDirPath() + "/..");
		if (cmd.isSet(basedirOption))
			baseDir.setPath(cmd.value(basedirOption));
		QString baseDirPath = baseDir.absolutePath() + "/";
		CUTEHMI_DEBUG("Base directory: " << baseDirPath);

		CUTEHMI_DEBUG("Library paths: " << QCoreApplication::libraryPaths());

		std::unique_ptr<QQmlApplicationEngine> engine(new QQmlApplicationEngine);
		engine->addImportPath(baseDirPath + CUTEHMI_DIRS_EXTENSIONS_INSTALL_SUBDIR);

		CUTEHMI_DEBUG("QML import paths: " << engine->importPathList());

		CUTEHMI_INFO(QCoreApplication::translate("main", "Welcome to %1 %2. Type \\help to see the list of commands.").arg(CUTEHMI_CONSOLE_VENDOR).arg(CUTEHMI_CONSOLE_FRIENDLY_NAME));

		QStringList positionalArguments = cmd.positionalArguments();
		if (positionalArguments.length() > 0) {
			QString extension = positionalArguments.at(0);
			QString extensionBaseName = extension.left(extension.lastIndexOf('.'));
			QString extensionMajor = extension.right(extension.length() - extension.lastIndexOf('.') - 1);

			QString extensionMinor = cmd.value(minorOption);
			if (!extensionMinor.isEmpty()) {
				bool ok;
				extensionMinor.toUInt(& ok);
				if (!ok)
					throw Exception(QCoreApplication::translate("main", "Command line argument error: value of '%1' option must be a number.").arg(minorOption.names().last()));
			}

			QString extensionComponent = cmd.value(componentOption);

			QString extensionImportStatement;
			if (!extension.isEmpty()) {
				if (!extensionMinor.isEmpty())
					extensionImportStatement = QString("import %1 %2.%3").arg(extensionBaseName).arg(extensionMajor).arg(extensionMinor);
				else
					extensionImportStatement = QString("import %1 %2").arg(extensionBaseName).arg(extensionMajor);
			}

			engine->loadData((extensionImportStatement + "\n" + extensionComponent + "{}").toLocal8Bit());
		}

		InputHandler inputHandler;
		Interpreter interpreter(engine.get());
		QObject::connect(& inputHandler, & InputHandler::lineRead, & interpreter, & Interpreter::interperetLine, Qt::QueuedConnection);
		QObject::connect(& interpreter, & Interpreter::lineInterpreted, & inputHandler, & InputHandler::readLine, Qt::QueuedConnection);
		inputHandler.readLine();

		return app.exec();

		//</Qt-Qt_5_7_0_Reference_Documentation-Threads_and_QObjects-QObject_Reentrancy-creating_QObjects_before_QApplication.assumption>

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

	return EXIT_FAILURE;

}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
