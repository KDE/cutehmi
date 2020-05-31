#include "../cutehmi.metadata.hpp"
#include "../cutehmi.dirs.hpp"
#include "cutehmi/cmd/logging.hpp"
#include "cutehmi/cmd/Exception.hpp"

#include <cutehmi/Messenger.hpp>

#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include <QCommandLineParser>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include <QtGlobal>
#include <QQmlComponent>

using namespace cutehmi::cmd;

/**
 * Main function.
 * @param argc number of arguments passed to the program.
 * @param argv list of arguments passed to the program.
 * @return return code.
 */
int main(int argc, char * argv[])
{
	// Set up application.

	QCoreApplication::setOrganizationName(CUTEHMI_CMD_VENDOR);
	QCoreApplication::setOrganizationDomain(CUTEHMI_CMD_DOMAIN);
	QCoreApplication::setApplicationName(CUTEHMI_CMD_FRIENDLY_NAME);
	QCoreApplication::setApplicationVersion(QString("%1.%2.%3").arg(CUTEHMI_CMD_MAJOR).arg(CUTEHMI_CMD_MINOR).arg(CUTEHMI_CMD_MICRO));

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
		QString translationFilePrefix = QString(CUTEHMI_CMD_NAME).replace('.', '-') + "_";
		QString translationFile = translationFilePrefix + language;
		if (!translator.load(translationFile, translationsDir))
			CUTEHMI_WARNING("Could not load translations file '" << translationFile << "'.");
		app.installTranslator(& translator);


		// Configure command line parser and process arguments.

		QCommandLineParser cmd;
		cmd.setApplicationDescription(CUTEHMI_CMD_TRANSLATED_FRIENDLY_NAME + "\n" + CUTEHMI_CMD_TRANSLATED_DESCRIPTION);
		cmd.addHelpOption();
		cmd.addVersionOption();

		QCommandLineOption langOption("lang", QCoreApplication::translate("main", "Choose application <language>."), QCoreApplication::translate("main", "language"));
		langOption.setDefaultValue(language);
		cmd.addOption(langOption);

		QCommandLineOption basedirOption("basedir", QCoreApplication::translate("main", "Set base directory to <dir>."), QCoreApplication::translate("main", "dir"));
		cmd.addOption(basedirOption);

		QCommandLineOption extensionOption({"e", "extension"}, QCoreApplication::translate("main", "Use extension <name> as QML extension to import."), QCoreApplication::translate("main", "name"));
		cmd.addOption(extensionOption);

		QCommandLineOption minorOption({"m", "minor"}, QCoreApplication::translate("main", "Use <version> for extension minor version to import."), QCoreApplication::translate("main", "version"));
		cmd.addOption(minorOption);

		QCommandLineOption scriptOption({"s", "script"}, QCoreApplication::translate("main", "Script <code> to evaluate."), QCoreApplication::translate("main", "code"));
		cmd.addOption(scriptOption);

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
		QObject::connect(engine.get(), & QQmlEngine::warnings, [](const QList<QQmlError> & warnings) {
			for (auto error : warnings)
				CUTEHMI_CRITICAL("Script error: " << error.description());
			exit(EXIT_FAILURE);
		});

		CUTEHMI_DEBUG("QML import paths: " << engine->importPathList());

		QString extension = cmd.value(extensionOption);
		QString extensionBaseName = extension.left(extension.lastIndexOf('.'));
		QString extensionMajor = extension.right(extension.length() - extension.lastIndexOf('.') - 1);

		QString extensionMinor = cmd.value(minorOption);
		if (!extensionMinor.isEmpty()) {
			bool ok;
			extensionMinor.toUInt(& ok);
			if (!ok)
				throw Exception(QCoreApplication::translate("main", "Command line argument error: value of '%1' option must be a number.").arg(minorOption.names().last()));
		}

		QString importStatement;
		if (!extension.isEmpty()) {
			if (!extensionMinor.isEmpty())
				importStatement = QString("import %1 %2.%3").arg(extensionBaseName).arg(extensionMajor).arg(extensionMinor);
			else
				importStatement = QString("import %1 %2").arg(extensionBaseName).arg(extensionMajor);
		}

		QString script = cmd.value(scriptOption);

		QStringList code;
		code << "import QtQml 2.0 as QtQml"
				<< importStatement
				<< "QtQml.QtObject {"
				<< "property var script: function() { " << script << "}"
				<< "QtQml.Component.onCompleted: { script(); Qt.quit(); }"
				<< "}";

		QQmlComponent component(engine.get());
		component.setData(code.join('\n').toLocal8Bit().constData(), QUrl());
		component.create();

		if (component.isError())
			for (auto error : component.errors())
				CUTEHMI_CRITICAL("Script error: " << error.description());
		else
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

	return  EXIT_FAILURE;

}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
