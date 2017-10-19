#include "../../include/base/Project.hpp"
#include "../../include/base/Exception.hpp"
#include "../../include/base/internal/ProjectXMLBackend.hpp"

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
	return m->pluginLoader.get();
}

ProjectModel * Project::model() const
{
	return m->model.get();
}

void Project::loadXMLFile(const QString & filePath, QQmlContext * qmlContext)
{
	if (filePath.isEmpty()) {
		Prompt::Warning(tr("Empty filename."));
		return;
	}

	CUTEHMI_BASE_QDEBUG("Loading project file '" << filePath << "'...");

	QFile file(filePath);
	if (file.open(QIODevice::ReadOnly)) {
		utils::MPtr<Members> newM(new Members);
		internal::ProjectXMLBackend xmlBackend(newM->model.get(), newM->pluginLoader.get(), qmlContext);
		try {
			xmlBackend.load(file);
			m.swap(newM);
			emit modelChanged();
			emit pluginLoaderChanged();
			Notification::Note(tr("Succesfuly loaded project file '%1'.").arg(filePath));
		} catch (const Exception & e) {
			Prompt::Critical(tr("Error while parsing '%1' document.").arg(filePath) + "\n\n" + e.what());
		}
		file.close();
	} else {
		if (!QFileInfo(filePath).exists())
			Prompt::Warning(tr("Could not load project file. File '%1' does not exist.").arg(filePath));
		else
			Prompt::Warning(tr("Could not load project file. File '%1' could not be opened.").arg(filePath));
	}
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
