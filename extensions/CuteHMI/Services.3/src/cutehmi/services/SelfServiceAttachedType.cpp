#include <cutehmi/services/SelfServiceAttachedType.hpp>

namespace cutehmi {
namespace services {

SelfServiceAttachedType::SelfServiceAttachedType(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

QString SelfServiceAttachedType::status() const
{
	return m->status;
}

void SelfServiceAttachedType::setStatus(const QString & status)
{
	if (m->status != status) {
		m->status = status;
		emit statusChanged();
	}
}

void SelfServiceAttachedType::resetStatus()
{
	m->status.clear();
	emit statusChanged();
}

}
}
