#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_STATEINTERFACE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_STATEINTERFACE_HPP

#include "internal/common.hpp"
#include "StartedStateInterface.hpp"

#include <QObject>
#include <QAbstractState>

namespace cutehmi {
namespace services {

class CUTEHMI_SERVICES_API StateInterface:
	public QObject
{
		Q_OBJECT

	public:
		Q_PROPERTY(QAbstractState * stopped READ stopped NOTIFY stoppedChanged)

		Q_PROPERTY(QAbstractState * starting READ starting NOTIFY startingChanged)

		Q_PROPERTY(QAbstractState * started READ started NOTIFY startedChanged)

		Q_PROPERTY(QAbstractState * stopping READ stopping NOTIFY stoppingChanged)

		Q_PROPERTY(QAbstractState * broken READ broken NOTIFY brokenChanged)

		Q_PROPERTY(QAbstractState * repairing READ repairing NOTIFY repairingChanged)

		Q_PROPERTY(QAbstractState * evacuating READ evacuating NOTIFY evacuatingChanged)

		Q_PROPERTY(QAbstractState * interrupted READ interrupted NOTIFY interruptedChanged)

		Q_PROPERTY(cutehmi::services::StartedStateInterface * startedStates READ startedStates CONSTANT)

		QAbstractState * stopped() const;

		QAbstractState * starting() const;

		QAbstractState * started() const;

		QAbstractState * stopping() const;

		QAbstractState * broken() const;

		QAbstractState * repairing() const;

		QAbstractState * evacuating() const;

		QAbstractState * interrupted() const;

		cutehmi::services::StartedStateInterface * startedStates() const;

		/**
		 * Find state by its name. States can be given name using QObject::setObjectName() function. Standard states have following
		 * names:
		 * - @p "stopped"
		 * - @p "interrupted"
		 * - @p "starting"
		 * - @p "started"
		 * - @p "stopping"
		 * - @p "broken"
		 * - @p "repairing"
		 * - @p "evacuating"
		 * - @p "started.active"
		 * - @p "started.idling"
		 * - @p "started.yielding"
		 * .
		 * @param name state name.
		 * @return state.
		 */
		Q_INVOKABLE QAbstractState * findState(const QString & name) const;

	signals:
		void stoppedChanged();

		void startingChanged();

		void startedChanged();

		void stoppingChanged();

		void brokenChanged();

		void repairingChanged();

		void evacuatingChanged();

		void interruptedChanged();

	protected:
		StateInterface();

		void setStopped(QAbstractState * stopped);

		void setStarting(QAbstractState * starting);

		void setStarted(QAbstractState * started, QAbstractState * yielding, QAbstractState * active, QAbstractState * idling);

		void setStopping(QAbstractState * stopping);

		void setBroken(QAbstractState * broken);

		void setRepairing(QAbstractState * repairing);

		void setEvacuating(QAbstractState * evacuating);

		void setInterrupted(QAbstractState * interrupted);

	private:
		struct Members {
			QAbstractState * stopped;
			QAbstractState * starting;
			QAbstractState * started;
			QAbstractState * stopping;
			QAbstractState * broken;
			QAbstractState * repairing;
			QAbstractState * evacuating;
			QAbstractState * interrupted;
			StartedStateInterface * startedStateInterface;
		};

		MPtr<Members> m;
};

}
}

#endif
