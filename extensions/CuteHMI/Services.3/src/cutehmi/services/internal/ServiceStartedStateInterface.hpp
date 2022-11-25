#ifndef CUTEHMI_SERVICES_INTERNAL_SERVICESTARTEDSTATEINTERFACE_HPP
#define CUTEHMI_SERVICES_INTERNAL_SERVICESTARTEDSTATEINTERFACE_HPP

#include <cutehmi/services/internal/common.hpp>
#include <cutehmi/services/StartedStateInterface.hpp>
#include <cutehmi/services/Serviceable.hpp>

namespace cutehmi {
namespace services {
namespace internal {

class ServiceStateInterface;

class CUTEHMI_SERVICES_PRIVATE ServiceStartedStateInterface:
	public StartedStateInterface
{
		friend class ServiceStateInterface;

	public:
		QAbstractState * yielding() const override;

		QAbstractState * active() const override;

		QAbstractState * idling() const override;

	protected:
		ServiceStartedStateInterface(ServiceStateInterface * parent, QState * started);

		void setStarted(QState * started);

		void replaceTransitionToIdling(const Serviceable & serviceable);

		void replaceTransitionToYielding(const Serviceable & serviceable);

		ServiceStateInterface * stateInterface() const;

		QState * idlingPersistent() const;

		QState * yieldingPersistent() const;

		QState * activePersistent() const;

		QState * idlingEphemeric() const;

		QState * yieldingEphemeric() const;

		QState * activeEphemeric() const;

		QAbstractTransition *& yieldingTransition(int index);

		QAbstractTransition * const & yieldingTransition(int index) const;

		QAbstractTransition *& activeTransition(int index);

		QAbstractTransition * const & activeTransition(int index) const;

		QAbstractTransition *& idlingTransition(int index);

		QAbstractTransition * const & idlingTransition(int index) const;

		void initializePersistentStates();

		void resetEphemericStates();

		void resetYieldingEphemeric();

		void resetActiveEphemeric();

		void resetIdlingEphemeric();

		void setUpYielding(bool reconfigure, const Serviceable & serviceable);

		void setUpActive(bool reconfigure, const Serviceable & serviceable);

		void setUpIdling(bool reconfigure, const Serviceable & serviceable);

		void addYieldingTransition(int index);

		void addIdlingTransition(int index, const Serviceable & serviceable);

		void addActiveTransition(int index, const Serviceable & serviceable);

	private:
		struct Members {
			struct {
				QState * persistent;
				QState * ephemeric;
				std::array<QAbstractTransition *, 1> transitions;
			} idling;
			struct {
				QState * persistent;
				QState * ephemeric;
				std::array<QAbstractTransition *, 1> transitions;
			} yielding;
			struct {
				QState * persistent;
				QState * ephemeric;
				std::array<QAbstractTransition *, 1> transitions;
			} active;
		};

		MPtr<Members> m;
};

}
}
}

#endif
