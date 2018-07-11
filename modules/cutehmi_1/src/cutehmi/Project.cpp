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

const QQmlListProperty<Plugin> & Project::plugins() const
{
	return *m->plugins.get();
}

void Project::load(IProjectBackend & backend) noexcept(false)
{
	MPtr<Members> newM(new Members);
	backend.load(ProjectPluginLoader(newM->pluginLoader.get()), newM->model->root());
	m.swap(newM);
	emit modelChanged();
	emit pluginsChanged();
}

void Project::reset()
{
	MPtr<Members> newM(new Members);
	m.swap(newM);
	emit modelChanged();
	emit pluginsChanged();
}

internal::PluginLoader * Project::pluginLoader() const
{
	return m->pluginLoader.get();
}

int Project::PluginsCount(QQmlListProperty<Plugin> * property)
{
	return static_cast<const internal::PluginLoader::LoadedPluginsContainer *>(property->data)->count();
}

Plugin * Project::PluginsAt(QQmlListProperty<Plugin> * property, int index)
{
	return static_cast<const internal::PluginLoader::LoadedPluginsContainer *>(property->data)->at(index);
}

}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
