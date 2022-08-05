#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_SERVICE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_2_INCLUDE_CUTEHMI_SERVICES_SERVICE_HPP

#include "internal/common.hpp"
#include "internal/StateInterface.hpp"
#include "Serviceable.hpp"

#include <QString>
#include <QVariant>
#include <QObject>
#include <QStateMachine>
#include <QTimer>
#include <QQmlEngine>

namespace cutehmi {
namespace services {

/**
 * %Service. %Service object acts as a container that wraps Serviceable instance and makes it accessible through QObject properties
 * defined by it. This approach decouples state interface API from the rest of QObject allowing classes to implement interface,
 * without disturbing their, perhaps more natural, hierarchy (class may inherit only after a single QObject).
 */
class CUTEHMI_SERVICES_API Service:
	public QObject
{
		Q_OBJECT
		QML_NAMED_ELEMENT(Service)

		friend class ServiceManager;

	public:
		static constexpr int INITIAL_STOP_TIMEOUT = 30000;
		static constexpr int INITIAL_START_TIMEOUT = 30000;
		static constexpr int INITIAL_REPAIR_TIMEOUT = 30000;
		static constexpr const char * INITIAL_NAME = "Unnamed Service";

		Q_PROPERTY(int stopTimeout READ stopTimeout WRITE setStopTimeout NOTIFY stopTimeoutChanged)
		Q_PROPERTY(int startTimeout READ startTimeout WRITE setStartTimeout NOTIFY startTimeoutChanged)
		Q_PROPERTY(int repairTimeout READ repairTimeout WRITE setRepairTimeout NOTIFY repairTimeoutChanged)
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString status READ status NOTIFY statusChanged)
		Q_PROPERTY(QVariant serviceable READ serviceable WRITE setServiceable NOTIFY serviceableChanged)

		Q_CLASSINFO("DefaultProperty", "serviceable")

		Service(QObject * parent = nullptr);

		~Service() override;

		int stopTimeout() const;

		/**
		 * Set stop timeout.
		 * @param stopTimeout amount of time [milliseconds] after which stopping or evacuating sequence should be interrupted.
		 * Setting a negative value will disable timeout functionality.
		 */
		void setStopTimeout(int stopTimeout);

		int startTimeout() const;

		/**
		 * Set start timeout.
		 * @param startTimeout amount of time [milliseconds] after which starting sequence should be interrupted. Setting a negative
		 * value will disable timeout functionality.
		 */
		void setStartTimeout(int startTimeout);

		int repairTimeout() const;

		/**
		 * Set repair timeout.
		 * @param repairTimeout amount of time [milliseconds] after which repair sequence should be interrupted. Setting a negative
		 * value will disable timeout functionality.
		 */
		void setRepairTimeout(int repairTimeout);

		QString name() const;

		void setName(const QString & name);

		QString status() const;

		/**
		 * Set serviced object. Object must implement Serviceable interface. Whole communication between service and
		 * @a serviceable is accomplished through state interface. State interface can not be accessed directly. Instead,
		 * @a serviceable is asked to configure states of the service via Serviceable interface.
		 * @param serviceable serviceable object to be maintained by this service. Object must implement Serviceable interface.
		 */
		void setServiceable(QVariant serviceable);

		/**
		 * Get serviced object.
		 * @return serviced object. QVariant wraps Serviceable * pointer.
		 */
		QVariant serviceable() const;

		/**
		 * Find state by its name. States can be given name using QObject::setObjectName() function. Standard states are given
		 * appropriate names:
		 * - @p "stopped"
		 * - @p "interrupted"
		 * - @p "starting"
		 * - @p "started"
		 * - @p "stopping"
		 * - @p "broken"
		 * - @p "repairing"
		 * - @p "evacuating"
		 * - @p "active"
		 * - @p "idling"
		 * - @p "yielding"
		 * .
		 * @param name state name.
		 * @return state.
		 */
		Q_INVOKABLE QAbstractState * findState(const QString & name) const;

	public slots:
		void start();

		void stop();

	signals:
		void stopTimeoutChanged();

		void startTimeoutChanged();

		void repairTimeoutChanged();

		void nameChanged();

		void statusChanged();

		void serviceableChanged();

		void started();

		void stopped();

		void activated();

	protected:
		internal::StateInterface * stateInterface();

		const internal::StateInterface * stateInterface() const;

	protected slots:
		void activate();

		void setStatus(const QString & status);

	private:
		static QString & DefaultStatus();

		void destroyStateMachine();

		void initializeStateMachine(Serviceable & serviceable);

		void addTransition(QState * source, QState * target, std::unique_ptr<QAbstractTransition>);

		void addStatuses(std::unique_ptr<Serviceable::ServiceStatuses> statuses);

		struct Members {
			int stopTimeout = INITIAL_STOP_TIMEOUT;
			int startTimeout = INITIAL_START_TIMEOUT;
			int repairTimeout = INITIAL_REPAIR_TIMEOUT;
			QString name = INITIAL_NAME;
			QString status;
			Serviceable * serviceable = nullptr;
			QStateMachine * stateMachine = nullptr;
			internal::StateInterface * stateInterface = nullptr;
			QTimer timeoutTimer;
			QState * lastNotifiableState = nullptr;
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
