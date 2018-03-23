#include "../../include/cutehmi/Plugin.hpp"

namespace cutehmi {

Plugin::Plugin(const QString & binary, std::unique_ptr<QPluginLoader> loader, const MetaData & metaData, QObject * parent):
	QObject(parent),
	m(new Members{binary, std::move(loader), metaData})
{
}

Plugin::~Plugin()
{
	if (m->loader->unload())
		CUTEHMI_LOG_DEBUG("Unloaded plugin '" << binary() << "'.");
	else
		CUTEHMI_LOG_WARNING("Could not unload plugin '" << binary() << "'.");
}

const QString & Plugin::binary() const
{
	return m->binary;
}

const QPluginLoader & Plugin::loader() const
{
	return *m->loader;
}

QObject * Plugin::instance()
{
	return m->loader->instance();
}

const QString & Plugin::id() const
{
	return m->metaData.id;
}

const QString & Plugin::name() const
{
	return m->metaData.name;
}

int Plugin::minor() const
{
	return m->metaData.minor;
}

int Plugin::micro() const
{
	return m->metaData.micro;
}

QString Plugin::version() const
{
	QString result;
	if (minor() == -1)
		result += "undefined";
	else
		result += QString::number(minor());

	result += ".";

	if (micro() == -1)
		result += "undefined";
	else
		result += QString::number(micro());

	return result;
}

}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
