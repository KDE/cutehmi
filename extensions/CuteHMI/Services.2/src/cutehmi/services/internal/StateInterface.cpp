#include <cutehmi/services/internal/StateInterface.hpp>

namespace cutehmi {
namespace services {
namespace internal {

StateInterface::StateInterface(QObject * parent):
	QObject(parent),
	m(new Members)
{
	m->mainStates[Members::STARTED].setInitialState(m->yielding);

	m->mainStates[Members::STOPPED].setObjectName("stopped");
	m->mainStates[Members::INTERRUPTED].setObjectName("interrupted");
	m->mainStates[Members::STARTING].setObjectName("starting");
	m->mainStates[Members::STARTED].setObjectName("started");
	m->mainStates[Members::STOPPING].setObjectName("stopping");
	m->mainStates[Members::BROKEN].setObjectName("broken");
	m->mainStates[Members::REPAIRING].setObjectName("repairing");
	m->active->setObjectName("active");
	m->idling->setObjectName("idling");
	m->yielding->setObjectName("yielding");
}

QString StateInterface::status() const
{
	return m->status;
}

void StateInterface::setStatus(const QString & status)
{
	if (m->status != status) {
		m->status = status;
		emit statusChanged();
	}
}

QAbstractState * StateInterface::find(const QString & name)
{
	for (auto state = m->mainStates.begin(); state != m->mainStates.end(); ++state) {
		if (name == state->objectName())
			return & (*state);
		QAbstractState * child = state->findChild<QAbstractState *>(name);
		if (child)
			return child;
	}
	return nullptr;
}

QState & StateInterface::stopped()
{
	return m->mainStates[Members::STOPPED];
}

const QState & StateInterface::stopped() const
{
	return m->mainStates[Members::STOPPED];
}

QState & StateInterface::interrupted()
{
	return m->mainStates[Members::INTERRUPTED];
}

const QState & StateInterface::interrupted() const
{
	return m->mainStates[Members::INTERRUPTED];
}

QState & StateInterface::starting()
{
	return m->mainStates[Members::STARTING];
}

const QState & StateInterface::starting() const
{
	return m->mainStates[Members::STARTING];
}

QState & StateInterface::started()
{
	return m->mainStates[Members::STARTED];
}

const QState & StateInterface::started() const
{
	return m->mainStates[Members::STARTED];
}

QState & StateInterface::idling()
{
	return *m->idling;
}

const QState & StateInterface::idling() const
{
	return *m->idling;
}

QState & StateInterface::yielding()
{
	return *m->yielding;
}

const QState & StateInterface::yielding() const
{
	return *m->yielding;
}

QState & StateInterface::active()
{
	return *m->active;
}

const QState & StateInterface::active() const
{
	return *m->active;
}

QState & StateInterface::stopping()
{
	return m->mainStates[Members::STOPPING];
}

const QState & StateInterface::stopping() const
{
	return m->mainStates[Members::STOPPING];
}

QState & StateInterface::broken()
{
	return m->mainStates[Members::BROKEN];
}

const QState & StateInterface::borken() const
{
	return m->mainStates[Members::BROKEN];
}

QState & StateInterface::repairing()
{
	return m->mainStates[Members::REPAIRING];
}

const QState & StateInterface::repairing() const
{
	return m->mainStates[Members::REPAIRING];
}

}
}
}
