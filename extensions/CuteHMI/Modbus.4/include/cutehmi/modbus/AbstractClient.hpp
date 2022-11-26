#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_4_INCLUDE_CUTEHMI_MODBUS_ABSTRACTCLIENT_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_4_INCLUDE_CUTEHMI_MODBUS_ABSTRACTCLIENT_HPP

#include "AbstractDevice.hpp"

#include "internal/PollingIterator.hpp"

#include <QQmlEngine>
#include <QQueue>
#include <QTimer>

namespace cutehmi {
namespace modbus {

/**
 * Abstract client.
 *
 * Abstract client can perform polling to update register values. This is handled by cutehmi::services::Service - the client just
 * needs to be set as its @ref cutehmi::services::Service::serviceable "serviceable" object.
 *
 * During polling a sequence of tasks is being processed. A task is usually a single request-response exchange performed to update
 * register value. During polling all awaken registers are updated. Intervals between complete polling sequences and individual
 * tasks can be with @ref pollingInterval and @ref pollingTaskInterval properties respectively.
 *
 * To protect Modbus device from flooding it with too many requests @ref requestInterval property can be used. If requests are
 * comming too fast they will be queued and sent to the device one by one in constant intervals.
 *
 * @remark Client becomes ready to handle requests only when it establishes connection with server.
 */
class CUTEHMI_MODBUS_API AbstractClient:
	public cutehmi::modbus::AbstractDevice
{
		Q_OBJECT
		QML_NAMED_ELEMENT(AbstractClient)
		QML_UNCREATABLE("AbstractClient is an abstract class")

	public:
		static constexpr int INITIAL_POLLING_INTERVAL = 250;

		static constexpr int INITIAL_POLLING_TASK_INTERVAL = 10;

		static constexpr int INITIAL_REQUEST_INTERVAL = 5;

		/**
		 * Time interval between complete polling sequences [ms].
		 */
		Q_PROPERTY(int pollingInterval READ pollingInterval WRITE setPollingInterval NOTIFY pollingIntervalChanged)

		/**
		 * Time interval between individual polling tasks [ms]. Task is usually a single request-response exchange performed to
		 * update register value.
		 */
		Q_PROPERTY(int pollingTaskInterval READ pollingTaskInterval WRITE setPollingTaskInterval NOTIFY pollingTaskIntervalChanged)

		/**
		 * Time interval between any individual requests [ms].
		 *
		 * @note this property is not mutually exclusive with @ref pollingTaskInterval. Property @ref pollingTaskInterval is used
		 * for polling only, while this property controls the interval between any Modbus requests. Requests can not be sent faster
		 * than specified by @a requestInterval. If value of @ref pollingTaskInterval is lower, this property enforces its
		 * precedence.
		 *
		 * @note subtle difference between @a pollingTaskInterval and @a requestInterval is that first one measures interval between
		 * last response and new request, while this one measures interval between last request and new request.
		 */
		Q_PROPERTY(int requestInterval READ requestInterval WRITE setRequestInterval NOTIFY requestIntervalChanged)

		/**
		 * Modbus response timeout [ms].
		 */
		Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged STORED false)

		int pollingInterval() const;

		void setPollingInterval(int interval);

		int pollingTaskInterval() const;

		void setPollingTaskInterval(int interval);

		int requestInterval() const;

		void setRequestInterval(int interval);

		virtual int timeout() const = 0;

		virtual void setTimeout(int timeout) = 0;

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

	signals:
		void pollingIntervalChanged();

		void pollingTaskIntervalChanged();

		void requestIntervalChanged();

		void timeoutChanged();

	protected:
		AbstractClient(QObject * parent = nullptr);

		void handleRequest(const QJsonObject & request) override;

		void handleReply(QUuid requestId, QJsonObject reply) override;

	protected slots:
		virtual void onStateChanged();

		void poll();

		void pollingTask();

	protected:
		Q_SIGNAL void requestAccepted(QJsonObject request);

		Q_SIGNAL void pollingRequested();

		Q_SIGNAL void pollingFinished();

		Q_SIGNAL void pollingTaskRequested();

		Q_SIGNAL void pollingTaskFinished();

	private slots:
		void dequeueRequest();

	private:
		typedef QQueue<QJsonObject> RequestQueueContainer;

		struct Members {
			internal::PollingIterator pollingIterator;
			int pollingInterval;
			int pollingTaskInterval;
			int requestInterval;
			qint64 lastProcessRequestTimestamp;
			QTimer requestDequeueTimer;
			RequestQueueContainer requestQueue;

			Members(AbstractDevice * device):
				pollingIterator(device),
				pollingInterval(INITIAL_POLLING_INTERVAL),
				pollingTaskInterval(INITIAL_POLLING_TASK_INTERVAL),
				requestInterval(INITIAL_REQUEST_INTERVAL),
				lastProcessRequestTimestamp(0)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
