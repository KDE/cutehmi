#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_3_INCLUDE_CUTEHMI_MODBUS_ABSTRACTCLIENT_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_3_INCLUDE_CUTEHMI_MODBUS_ABSTRACTCLIENT_HPP

#include "AbstractDevice.hpp"

#include "internal/PollingIterator.hpp"

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
		static constexpr int INITIAL_POLLING_INTERVAL = 250;

		static constexpr int INITIAL_POLLING_TASK_INTERVAL = 10;

		Q_PROPERTY(int pollingInterval READ pollingInterval WRITE setPollingInterval NOTIFY pollingIntervalChanged)

		Q_PROPERTY(int pollingTaskInterval READ pollingTaskInterval WRITE setPollingTaskInterval NOTIFY pollingTaskIntervalChanged)

		int pollingInterval() const;

		void setPollingInterval(int interval);

		int pollingTaskInterval() const;

		void setPollingTaskInterval(int interval);

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

	signals:
		void pollingIntervalChanged();

		void pollingTaskIntervalChanged();

	protected:
		AbstractClient(QObject * parent = nullptr);

		void handleRequest(const QJsonObject & request) override;

		void handleReply(QUuid requestId, QJsonObject reply) override;

	protected slots:
		virtual void onStateChanged();

		void poll();

		void pollingTask();

	protected:
		Q_SIGNAL void requestReceived(QJsonObject request);

		Q_SIGNAL void pollingRequested();

		Q_SIGNAL void pollingFinished();

		Q_SIGNAL void pollingTaskRequested();

		Q_SIGNAL void pollingTaskFinished();

	private:
		struct Members {
			internal::PollingIterator pollingIterator;
			int pollingInterval;
			int pollingTaskInterval;

			Members(AbstractDevice * device):
				pollingIterator(device),
				pollingInterval(INITIAL_POLLING_INTERVAL),
				pollingTaskInterval(INITIAL_POLLING_TASK_INTERVAL)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2021, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
