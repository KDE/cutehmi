#include "../../include/base/Plugin.hpp"

namespace cutehmi {
namespace base {

Plugin::Plugin(const QString & binary, QObject * instance, const MetaData & metaData, QObject * parent):
	QObject(parent),
	m(new Members{binary, instance, metaData})
{
}

const QString & Plugin::binary() const
{
	return m->binary;
}

QObject * Plugin::instance()
{
	return m->instance;
}

const QString & Plugin::id() const
{
	return m->metaData.id;
}

const QString & Plugin::name() const
{
	return m->metaData.name;
}

const QString & Plugin::version() const
{
	return m->metaData.version;
}


}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
