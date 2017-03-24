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
