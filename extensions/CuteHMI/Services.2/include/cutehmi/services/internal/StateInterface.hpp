#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_INTERNAL_STATEINTERFACE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_INTERNAL_STATEINTERFACE_HPP

#include "common.hpp"

#include <QObject>
#include <QState>
#include <QSignalTransition>

#include <array>

namespace cutehmi {
namespace services {
namespace internal {

class CUTEHMI_SERVICES_API StateInterface:
	public QObject
{
		Q_OBJECT

	public:
		Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

		StateInterface(QObject * parent = nullptr);

		QString status() const;

		void setStatus(const QString & status);

		Q_INVOKABLE QAbstractState * find(const QString & name);

		QState & stopped();

		const QState & stopped() const;

		QState & interrupted();

		const QState & interrupted() const;

		QState & starting();

		const QState & starting() const;

		QState & started();

		const QState & started() const;

		QState & idling();

		const QState & idling() const;

		QState & yielding();

		const QState & yielding() const;

		QState & active();

		const QState & active() const;

		QState & stopping();

		const QState & stopping() const;

		QState & broken();

		const QState & borken() const;

		QState & repairing();

		const QState & repairing() const;

	signals:
		void statusChanged();

	private:
		struct Members
		{
			enum MainStateNames : std::size_t {
				STOPPED = 0,
				INTERRUPTED,
				STARTING,
				STARTED,
				STOPPING,
				BROKEN,
				REPAIRING
			};

			typedef std::array<QState, 7> MainStatesContainer;

			MainStatesContainer mainStates;
			QString status;
			QState * idling;
			QState * yielding;
			QState * active;

			Members():
				mainStates{},
				idling(new QState(& mainStates[STARTED])),
				yielding(new QState(& mainStates[STARTED])),
				active(new QState(& mainStates[STARTED]))
			{
			}
		};

		MPtr<Members> m;
};

}
}
}

#endif
