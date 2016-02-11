#include "ScreenObject.hpp"

namespace base {

ScreenObject::ScreenObject(const QString & source, QObject * parent):
	QObject(parent),
	m_source(source)
{
}

QString ScreenObject::source() const
{
	return m_source;
}

}
