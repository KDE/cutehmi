#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_SRC_CUTEHMI_SERVICES_INTERNAL_SERVICESTATEINTERFACE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_SRC_CUTEHMI_SERVICES_INTERNAL_SERVICESTATEINTERFACE_HPP

#include <cutehmi/services/internal/common.hpp>
#include <cutehmi/services/StateInterface.hpp>

#include <QState>

#include <memory>

namespace cutehmi {
namespace services {
namespace internal {

class ServiceStateMachine;

class CUTEHMI_SERVICES_PRIVATE ServiceStateInterface:
	public StateInterface
{
		Q_OBJECT

	public:
		ServiceStateInterface();

		void bindStateMachine(ServiceStateMachine * serviceStateMachine);

		void unbindStateMachine();

	private slots:
		void smSetStopped();

		void smSetStarting();

		void smSetStarted();

		void smSetStopping();

		void smSetBroken();

		void smSetRepairing();

		void smSetEvacuating();

		void smSetInterrupted();

	private:
		void setDummyStates();

		struct Members {
			std::unique_ptr<QState> dummyStopped;
			std::unique_ptr<QState> dummyStarting;
			std::unique_ptr<QState> dummyStarted;
			std::unique_ptr<QState> dummyStopping;
			std::unique_ptr<QState> dummyBroken;
			std::unique_ptr<QState> dummyRepairing;
			std::unique_ptr<QState> dummyEvacuating;
			std::unique_ptr<QState> dummyInterrupted;
			std::unique_ptr<QState> dummyStartedYielding;
			std::unique_ptr<QState> dummyStartedActive;
			std::unique_ptr<QState> dummyStartedIdling;
			ServiceStateMachine * serviceStateMachine;
		};

		MPtr<Members> m;
};

}
}
}

#endif
