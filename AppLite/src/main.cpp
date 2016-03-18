#include "version.hpp"

#include <base/ProjectModel.hpp>
#include <base/RunnersRegister.hpp>
#include <base/ErrorInfo.hpp>
#include <base/PluginLoader.hpp>
#include <base/XMLProjectBackend.hpp>
#include <base/ScreenObject.hpp>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QDir>
#include <QtDebug>
#include <QCommandLineParser>
#include <QQmlContext>
#include <QUrl>

namespace cutehmi {

struct LoadFileError:
	public base::Error
{
	enum : int {
		NOT_EXISTS = base::Error::SUBCLASS_BEGIN,
		UNABLE_TO_OPEN,
		EMPTY_FILENAME
	};

	using base::Error::Error;

	QString str() const;
};

QString LoadFileError::str() const
{
	switch (code()) {
		case NOT_EXISTS:
			return tr("File does not exist.");
		case UNABLE_TO_OPEN:
			return tr("Could not open file.");
		case EMPTY_FILENAME:
			return tr("Empty file name.");
		default:
			return base::Error::str();
	}
}

base::ErrorInfo loadFile(const QString & filePath, base::PluginLoader & pluginLoader, base::ProjectModel & projectModel)
{
	base::ErrorInfo result;

	if (filePath.isEmpty())
		return base::errorInfo(LoadFileError(LoadFileError::EMPTY_FILENAME));

	QFile file(filePath);
	if (file.open(QIODevice::ReadOnly)) {
		base::XMLProjectBackend xmlBackend(& projectModel, & pluginLoader);
		result = base::errorInfo(xmlBackend.load(file));
		if (result.code == base::Error::OK)
			qDebug() << "Loaded project file " << filePath << ".";
		file.close();
	} else {
		qWarning() << "Could not open file " << filePath;
		if (!QFileInfo(filePath).exists())
			return base::errorInfo(LoadFileError(LoadFileError::NOT_EXISTS));
		else
			return base::errorInfo(LoadFileError(LoadFileError::UNABLE_TO_OPEN));
	}
	return result;
}

void visitProjectContext(base::ProjectModel & model, QQmlContext & context)
{
	base::ProjectModel::Node::VisitorDelegate::QMLContextPropertyProxy proxy(& context);
	for (auto it = model.begin(); it != model.end(); ++it)
		it->visitorDelegate()->visit(proxy);
}

void visitRunnersRegister(base::ProjectModel & model, base::RunnersRegister & runners)
{
	base::ProjectModel::Node::VisitorDelegate::RunnersRegisterProxy proxy(& runners);
	for (auto it = model.begin(); it != model.end(); ++it)
		it->visitorDelegate()->visit(proxy);
}

QString findDefaultScreen(base::ProjectModel & model)
{
	for (auto it = model.begin(); it != model.end(); ++it)
		if (base::ScreenObject * screen = qobject_cast<base::ScreenObject *>(it->data().object()))
			if (screen->isDefault())
				return screen->source();
	return QString();
}

}

int main(int argc, char * argv[])
{
	static const char * PLUGINS_SUBDIR = "plugins";

	QCoreApplication::setOrganizationDomain("ekterm.pl");
	QCoreApplication::setApplicationName("CuteHMI Lite");
	QCoreApplication::setApplicationVersion(CUTEHMI_APPLITE_VERSION);

	QGuiApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/img/icon.png"));

	QCommandLineParser cmd;
	cmd.setApplicationDescription("CuteHMI Lite");
	cmd.addHelpOption();
	cmd.addVersionOption();
	QCommandLineOption fullScreenOption({"f", "fullscreen"}, QCoreApplication::translate("main", "Run application in full screen mode."));
	cmd.addOption(fullScreenOption);
	QCommandLineOption projectOption({"p", "project"}, QCoreApplication::translate("main", "Load CuteHMI project <file>."), QCoreApplication::translate("main", "file"));
	cmd.addOption(projectOption);
	QCommandLineOption stoppedOption({"s", "stopped"}, QCoreApplication::translate("main", "Do not start project."));
	cmd.addOption(stoppedOption);
	cmd.process(app);

	cutehmi::base::PluginLoader pluginLoader;
	QDir dir(qApp->applicationDirPath());
	dir.cd(PLUGINS_SUBDIR);
	pluginLoader.setPluginsDir(dir.canonicalPath());
	qDebug() << "Library paths: " << QCoreApplication::libraryPaths();

	// It's quite important to destroy "engine" before "projectModel", because ProjectModel contains context properties, which may still be in use by some QML components (for example in "Component.onDestroyed" handlers).
	cutehmi::base::ProjectModel projectModel; // Keep order (see above).
	QQmlApplicationEngine engine;	// Keep order (see above).
	engine.addImportPath("../CuteHMI/QML");
	engine.addImportPath("../QML");
	qDebug() << "QML import paths: " << engine.importPathList();

	cutehmi::base::RunnersRegister runners;
	cutehmi::base::ErrorInfo errorInfo = cutehmi::loadFile(cmd.value(projectOption), pluginLoader, projectModel);
	if (errorInfo.code == cutehmi::base::Error::OK) {
		cutehmi::visitRunnersRegister(projectModel, runners);
		cutehmi::visitProjectContext(projectModel, *engine.rootContext());
	} else
		qWarning() << "Following error occured while loading project file: " << errorInfo.str;

	QString defaultScreenPath = cutehmi::findDefaultScreen(projectModel);
	if (!defaultScreenPath.isEmpty()) {
		if (engine.rootContext()->contextProperty("defaultScreenUrl").isValid())
			qCritical() << "Can not load screen because \"defaultScreenUrl\" property has been already set.";
		else
			engine.rootContext()->setContextProperty("defaultScreenUrl", QUrl::fromLocalFile(defaultScreenPath).toString());
	}

	engine.load(QUrl(QStringLiteral("qrc:/qml/MainWindow.qml")));
	if (!cmd.isSet(stoppedOption))
		runners.start();
	else
		qWarning() << stoppedOption.description();

	return app.exec();
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
