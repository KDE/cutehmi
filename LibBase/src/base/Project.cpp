#include "../../include/base/Project.hpp"
#include "../../include/base/Exception.hpp"
#include "../../include/base/internal/ProjectXMLBackend.hpp"
#include "../../include/base/Message.hpp"

#include <QFile>
#include <QFileInfo>

namespace cutehmi {
namespace base {

Project::Project(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

Project::~Project()
{
}

PluginLoader * Project::pluginLoader() const
{
	return & m->pluginLoader;
}

ProjectModel * Project::model() const
{
	return & m->model;
}

void Project::loadXMLFile(const QString & filePath, QQmlContext * qmlContext)
{
	if (filePath.isEmpty()) {
		Message::Error(tr("Empty filename."));
		return;
	}

	CUTEHMI_BASE_QDEBUG("Loading project file \"" << filePath << "\"...");

	QFile file(filePath);
	if (file.open(QIODevice::ReadOnly)) {
		std::unique_ptr<Members> newM(new Members);
		internal::ProjectXMLBackend xmlBackend(& newM->model, & newM->pluginLoader, qmlContext);
		try {
			xmlBackend.load(file);
			m.swap(newM);
			emit modelChanged();
			emit pluginLoaderChanged();
			Message::Note(tr("Succesfuly loaded project file %1.").arg(filePath));
		} catch (const Exception & e) {
			Message::Error(e.what());
		}
		file.close();
	} else {
		if (!QFileInfo(filePath).exists())
			Message::Error(tr("Could not load project file. File %1 does not exist.").arg(filePath));
		else
			Message::Error(tr("Could not load project file. File %1 could not be opened.").arg(filePath));
	}
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
