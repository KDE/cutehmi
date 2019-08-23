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

namespace cutehmi {
namespace services {

/**
 * Service.
 */
class CUTEHMI_SERVICES_API Service:
	public QObject
{
		Q_OBJECT

		friend class ServiceManager;

	public:
		static constexpr int INITIAL_STOP_TIMEOUT = 30000;
		static constexpr const char * INITIAL_NAME = "Unnamed Service";

		Q_PROPERTY(int stopTimeout READ stopTimeout WRITE setStopTimeout NOTIFY stopTimeoutChanged)
		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
		Q_PROPERTY(QString status READ status NOTIFY statusChanged)
		Q_PROPERTY(QVariant serviceable READ serviceable WRITE setServiceable NOTIFY serviceableChanged)

		Q_CLASSINFO("DefaultProperty", "serviceable")

		Service(QObject * parent = nullptr);

		~Service() override;

		int stopTimeout() const;

		/**
		 * Set timeout.
		 * @param timeout amount of time [milliseconds] after which stopping sequence should be interrupted. Setting a negative
		 * value will disable timeout functionality.
		 */
		void setStopTimeout(int stopTimeout);

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

	public slots:
		void start();

		void stop();

	signals:
		void stopTimeoutChanged();

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
			QString name = INITIAL_NAME;
			QString status;
			Serviceable * serviceable = nullptr;
			QStateMachine * stateMachine = nullptr;
			internal::StateInterface * stateInterface = nullptr;
			QTimer timeoutTimer;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
