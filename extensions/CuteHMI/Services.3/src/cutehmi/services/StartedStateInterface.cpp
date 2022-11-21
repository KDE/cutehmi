#include <cutehmi/services/StartedStateInterface.hpp>

namespace cutehmi {
namespace services {

QAbstractState * StartedStateInterface::yielding() const
{
	return m->yielding;
}

QAbstractState * StartedStateInterface::active() const
{
	return m->active;
}

QAbstractState * StartedStateInterface::idling() const
{
	return m->idling;
}

StartedStateInterface::StartedStateInterface(QObject * parent):
	QObject(parent),
	m(new Members{
	nullptr,
	nullptr,
	nullptr})
{
}

void StartedStateInterface::setYielding(QAbstractState * yielding)
{
	if (m->yielding != yielding) {
		m->yielding = yielding;
		emit yieldingChanged();
	}
}

void StartedStateInterface::setActive(QAbstractState * active)
{
	if (m->active != active) {
		m->active = active;
		emit activeChanged();
	}
}

void StartedStateInterface::setIdling(QAbstractState * idling)
{
	if (m->idling != idling) {
		m->idling = idling;
		emit idlingChanged();
	}
}

}
}
