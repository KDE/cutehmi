#include "ScreenObject.hpp"

namespace cutehmi {
namespace base {

ScreenObject::ScreenObject(const QString & source, bool def, QObject * parent):
	QObject(parent),
	m_source(source),
	m_default(def)
{
}

QString ScreenObject::source() const
{
	return m_source;
}

void ScreenObject::setSource(const QString & source)
{
	m_source = source;
}

bool ScreenObject::isDefault() const
{
	return m_default;
}

void ScreenObject::setDefault(bool def)
{
	m_default = def;
}

}
}
