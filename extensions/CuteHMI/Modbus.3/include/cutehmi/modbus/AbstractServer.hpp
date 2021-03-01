#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_ABSTRACTSERVER_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_ABSTRACTSERVER_HPP

#include "AbstractDevice.hpp"

namespace cutehmi {
namespace modbus {

/**
 * Abstract server.
 *
 * @remark Server is always ready to handle requests, even if it is not in opened state (i.e. it does not listen for clients),
 * because requests are affecting server internal state.
 */
class CUTEHMI_MODBUS_API AbstractServer:
	public AbstractDevice
{
		Q_OBJECT

	public:
		static constexpr bool INITIAL_BUSY = false;

		Q_PROPERTY(bool busy READ busy WRITE setBusy NOTIFY busyChanged)

		bool busy() const;

		virtual void setBusy(bool busy) = 0;

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
		void busyChanged();

	protected:
		AbstractServer(QObject * parent = nullptr);

		void handleRequest(const QJsonObject & request) override;

	protected slots:
		virtual void handleCoilsWritten(quint16 address, quint16 amount);

		virtual void handleDiscreteInputsWritten(quint16 address, quint16 amount);

		virtual void handleHoldingRegistersWritten(quint16 address, quint16 amount);

		virtual void handleInputRegistersWritten(quint16 address, quint16 amount);

		void updateBusy(bool busy);

	CUTEHMI_PROTECTED_SIGNALS:
		void requestReceived(QJsonObject request);

	private:
		struct Members {
			bool busy = INITIAL_BUSY;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
