#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_ABSTRACTCLIENT_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_ABSTRACTCLIENT_HPP

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

#endif

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
