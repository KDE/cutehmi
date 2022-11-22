#ifndef CUTEHMI_SERVICES_SELFSERVICE_HPP
#define CUTEHMI_SERVICES_SELFSERVICE_HPP

#include "internal/common.hpp"

#include "AbstractService.hpp"
#include "Serviceable.hpp"

namespace cutehmi {
namespace services {

namespace internal {
class ServiceStateMachine;
class ServiceStateInterface;
}

class SelfServiceAttachedType;

/**
 * Self service.
 *
 * Self service is a service which implements Serviceable interface by itself and allows one to customize a bahavior through a bunch
 * of properties. This allows services to be defined within QML, as QML component must be a descendant of QObject and implementing
 * Serviceable in QML directly is not possible. For C++ classes it's typically more flexible and straightforward to implement
 * Serviceable interface and use Service as QML component which controls the serviceable object.
 */
class CUTEHMI_SERVICES_API SelfService:
	public cutehmi::services::AbstractService,
	public QQmlParserStatus,
	public Serviceable
{
		Q_OBJECT
		QML_ATTACHED(cutehmi::services::SelfServiceAttachedType)
		QML_NAMED_ELEMENT(SelfService)
		Q_INTERFACES(QQmlParserStatus)

	public:
		Q_PROPERTY(QAbstractState * startingState READ startingState WRITE setStartingState NOTIFY startingStateChanged)

		Q_PROPERTY(QAbstractState * activeState READ activeState WRITE setActiveState NOTIFY activeStateChanged)

		Q_PROPERTY(QAbstractState * stoppingState READ stoppingState WRITE setStoppingState NOTIFY stoppingStateChanged)

		Q_PROPERTY(QAbstractState * brokenState READ brokenState WRITE setBrokenState NOTIFY brokenStateChanged)

		Q_PROPERTY(QAbstractState * repairingState READ repairingState WRITE setRepairingState NOTIFY repairingStateChanged)

		Q_PROPERTY(QAbstractState * evacuatingState READ evacuatingState WRITE setEvacuatingState NOTIFY evacuatingStateChanged)

		Q_PROPERTY(QJSValue signalToStarted READ signalToStarted WRITE setSignalToStarted NOTIFY signalToStartedChanged)

		Q_PROPERTY(QJSValue signalToStopped READ signalToStopped WRITE setSignalToStopped NOTIFY signalToStoppedChanged)

		Q_PROPERTY(QJSValue signalToBroken READ signalToBroken WRITE setSignalToBroken NOTIFY signalToBrokenChanged)

		Q_PROPERTY(QJSValue signalToIdling READ signalToIdling WRITE setSignalToIdling NOTIFY signalToIdlingChanged)

		Q_PROPERTY(QJSValue signalToYielding READ signalToYielding WRITE setSignalToYielding NOTIFY signalToYieldingChanged)

		explicit SelfService(QObject * parent = nullptr);

		~SelfService() override;

		static cutehmi::services::SelfServiceAttachedType * qmlAttachedProperties(QObject * object);

		QAbstractState * startingState() const;

		void setStartingState(QAbstractState * startingState);

		QAbstractState * activeState() const;

		void setActiveState(QAbstractState * activeState);

		QAbstractState * stoppingState() const;

		void setStoppingState(QAbstractState * stoppingState);

		QAbstractState * repairingState() const;

		void setBrokenState(QAbstractState * brokenState);

		QAbstractState * brokenState() const;

		void setRepairingState(QAbstractState * repairingState);

		QAbstractState * evacuatingState() const;

		void setEvacuatingState(QAbstractState * evacuatingState);

		QJSValue signalToStarted() const;

		void setSignalToStarted(const QJSValue & signal);

		QJSValue signalToStopped() const;

		void setSignalToStopped(const QJSValue & signal);

		QJSValue signalToBroken() const;

		void setSignalToBroken(const QJSValue & signal);

		QJSValue signalToIdling() const;

		void setSignalToIdling(const QJSValue & signal);

		QJSValue signalToYielding() const;

		void setSignalToYielding(const QJSValue & signal);

		void configureStarting(QState * starting, AssignStatusFunction assignStatus) override;

		void configureStarted(QState * active, const QState * idling, const QState * yielding, AssignStatusFunction assignStatus) override;

		void configureStopping(QState * stopping, AssignStatusFunction assignStatus) override;

		void configureBroken(QState * broken, AssignStatusFunction assignStatus) override;

		void configureRepairing(QState * repairing, AssignStatusFunction assignStatus) override;

		void configureEvacuating(QState * evacuating, AssignStatusFunction assignStatus) override;

		std::unique_ptr<QAbstractTransition> transitionToStarted() const override;

		std::unique_ptr<QAbstractTransition> transitionToStopped() const override;

		std::unique_ptr<QAbstractTransition> transitionToBroken() const override;

		std::unique_ptr<QAbstractTransition> transitionToYielding() const override;

		std::unique_ptr<QAbstractTransition> transitionToIdling() const override;

		void classBegin() override;

		void componentComplete() override;

	signals:
		void startingStateChanged();

		void activeStateChanged();

		void stoppingStateChanged();

		void brokenStateChanged();

		void repairingStateChanged();

		void evacuatingStateChanged();

		void signalToStartedChanged();

		void signalToStoppedChanged();

		void signalToBrokenChanged();

		void signalToIdlingChanged();

		void signalToYieldingChanged();

	private:
		static const char * DSM_IMPORT_STATEMENT;

		static QString & DefaultStatus();

		internal::ServiceStateInterface * stateInterface() const;

		void assignStateStatuses(QState & state, AssignStatusFunction assignStatus);

		void assignStateStatus(QState & state, AssignStatusFunction assignStatus, const SelfServiceAttachedType * soAttachedType);

		//<CuteHMI.Services-4.workaround target="Qt" cause="missing">

		/**
		 * Extract sender and signal pair from QJSValue.
		 *
		 * This function makes a bridge to The State Machine Framework C++ API for properties dedicated to conveniently store
		 * signals in QML as QJSValue-s.
		 *
		 * @param qmlSignal value inside which QML signal is stored.
		 * @return a pair that consists of signal sender object and byte array with signal name.
		 */
		virtual std::pair<const QObject *, QByteArray> senderSignalPair(const QJSValue & qmlSignal) const;

		QQmlEngine * helperQmlEngine() const;

		QSignalTransition * helperSignalTransition() const;

		QJSValue helperSignalTransitionJSValue() const;

		//</CuteHMI.Services-4.workaround>

		void initializeStateMachine(bool start = true);

		void destroyStateMachine();

		struct Members
		{
			//<CuteHMI.Services-3.workaround target="Qt" cause="design">
			QStateMachine surrogateSM;
			//</CuteHMI.Services-3.workaround>
			QAbstractState * activeState;
			QAbstractState * startingState;
			QAbstractState * stoppingState;
			QAbstractState * brokenState;
			QAbstractState * repairingState;
			QAbstractState * evacuatingState;
			QSignalTransition * transitionToStartedState;
			QAbstractTransition * transitionToStoppedState;
			QAbstractTransition * transitionToBrokenState;
			QAbstractTransition * transitionToYieldingState;
			QAbstractTransition * transitionToIdlingState;
			QJSValue signalToStarted;
			QJSValue signalToStopped;
			QJSValue signalToBroken;
			QJSValue signalToIdling;
			QJSValue signalToYielding;
			internal::ServiceStateMachine * stateMachine;
			bool qmlBeingParsed;

			//<CuteHMI.Services-4.workaround target="Qt" cause="missing">
			mutable struct
			{
				mutable QQmlEngine * helperQmlEngine;
				mutable QSignalTransition * helperSignalTransition;
				mutable QJSValue helperSignalTransitionJSValue;
			} cache;
			//</CuteHMI.Services-4.workaround>
		};

		MPtr<Members> m;
};

}
}

#endif
