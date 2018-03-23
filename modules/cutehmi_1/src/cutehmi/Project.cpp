#include "../../include/cutehmi/Project.hpp"

namespace cutehmi {

Project::Project(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

Project::~Project()
{
}

ProjectModel * Project::model() const
{
	return m->model.get();
}

void Project::load(IProjectBackend & backend) noexcept(false)
{
	MPtr<Members> newM(new Members);
	backend.load(ProjectPluginLoader(newM->pluginLoader.get()), newM->model->root());
	m.swap(newM);
	emit modelChanged();
}

void Project::reset()
{
	MPtr<Members> newM(new Members);
	m.swap(newM);
	emit modelChanged();
}

internal::PluginLoader * Project::pluginLoader() const
{
	return m->pluginLoader.get();
}

}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
