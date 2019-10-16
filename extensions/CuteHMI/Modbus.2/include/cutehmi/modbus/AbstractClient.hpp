#ifndef INCLUDECUTEHMIMODBUSABSTRACTCLIENT_HPP
#define INCLUDECUTEHMIMODBUSABSTRACTCLIENT_HPP

#include "AbstractDevice.hpp"

#include "internal/PollingIterator.hpp"

#include <cutehmi/services/PollingTimer.hpp>

namespace cutehmi {
namespace modbus {

/**
 * Abstract client.
 *
 * @remark Client becomes ready to handle requests only when it establishes connection with server.
 */
class CUTEHMI_MODBUS_API AbstractClient:
	public AbstractDevice
{
		Q_OBJECT

	public:
		Q_PROPERTY(cutehmi::services::PollingTimer * pollingTimer READ pollingTimer CONSTANT)

		const services::PollingTimer * pollingTimer() const;

		services::PollingTimer * pollingTimer();

		std::unique_ptr<ServiceStatuses> configureStarting(QState * starting) override;

		std::unique_ptr<ServiceStatuses> configureStarted(QState * active, const QState * idling, const QState * yielding) override;

		std::unique_ptr<ServiceStatuses> configureStopping(QState * stopping) override;

		std::unique_ptr<ServiceStatuses> configureBroken(QState * broken) override;

		std::unique_ptr<ServiceStatuses> configureRepairing(QState * repairing) override;

		std::unique_ptr<ServiceStatuses> configureEvacuating(QState * evacuating) override;

		std::unique_ptr<QAbstractTransition> transitionToStarted() const override;

		std::unique_ptr<QAbstractTransition> transitionToStopped() const override;

		std::unique_ptr<QAbstractTransition> transitionToBroken() const override;

		std::unique_ptr<QAbstractTransition> transitionToYielding() const override;

		std::unique_ptr<QAbstractTransition> transitionToIdling() const override;

	protected:
		AbstractClient(QObject * parent = nullptr);

		void handleRequest(const QJsonObject & request) override;

		void handleReply(QUuid requestId, QJsonObject reply) override;

	protected slots:
		virtual void onStateChanged();

		void poll();

		void pollingTask();

	CUTEHMI_PROTECTED_SIGNALS:
		void requestReceived(QJsonObject request);

		void broke();

		void stopped();

		void started();

		void pollingFinished();

		void pollingTaskFinished();

	private:
		struct Members {
			internal::PollingIterator pollingIterator;
			services::PollingTimer pollingTimer;

			Members(AbstractDevice * device):
				pollingIterator(device)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif // INCLUDECUTEHMIMODBUSABSTRACTCLIENT_HPP
