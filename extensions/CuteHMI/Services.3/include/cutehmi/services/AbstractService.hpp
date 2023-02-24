#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_ABSTRACTSERVICE_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_ABSTRACTSERVICE_HPP

#include "internal/common.hpp"
#include "StateInterface.hpp"

//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
#include <cutehmi/workarounds/qt5compatibility/qsizetype.hpp>
//</CuteHMI.Workarounds.Qt5Compatibility-1.workaround>


//<CuteHMI.Workarounds.Qt5Compatibility-5.workaround target="Qt" cause="Qt5">

#include <cutehmi/workarounds/qt5compatibility/cutehmiQt6MocInclude.hpp>

namespace cutehmi {
namespace services {

class AbstractServiceController;

}
}

CUTEHMI_QT6_MOC_INCLUDE("AbstractServiceController.hpp")

//</CuteHMI.Workarounds.Qt5Compatibility-5.workaround>


#include <QObject>
#include <QString>
#include <QStateMachine>
#include <QTimer>
#include <QQmlEngine>
#include <QQmlListProperty>

namespace cutehmi {
namespace services {

/**
 * Abstract service.
 *
 * Guarantee is given that @ref states property is never @a nullptr, nor any of its states is ever @p nullptr and states are
 * persistent - they do not change. Subclasses have to take care to ensure that this guarantee is not violated. Additionaly they
 * should take care about initialized() signal, which should be emitted once the service has been initialized and it's ready to be
 * started. It is also well-seen if subclasses update service @a status accordingly to the service state during its lifecycle.
 */
class CUTEHMI_SERVICES_API AbstractService:
	public QObject
{
		Q_OBJECT
		QML_NAMED_ELEMENT(AbstractService)
		QML_UNCREATABLE("AbstractService is an abstract class")

	public:
		static constexpr int INITIAL_SHUTDOWN_TIMEOUT = 180000;

		static constexpr int INITIAL_STOP_TIMEOUT = 30000;

		static constexpr int INITIAL_START_TIMEOUT = 30000;

		static constexpr int INITIAL_REPAIR_TIMEOUT = 30000;

		static constexpr const char * INITIAL_NAME = "Unnamed Service";

		Q_PROPERTY(int shutdownTimeout READ shutdownTimeout WRITE setShutdownTimeout NOTIFY shutdownTimeoutChanged)

		Q_PROPERTY(int stopTimeout READ stopTimeout WRITE setStopTimeout NOTIFY stopTimeoutChanged)

		Q_PROPERTY(int startTimeout READ startTimeout WRITE setStartTimeout NOTIFY startTimeoutChanged)

		Q_PROPERTY(int repairTimeout READ repairTimeout WRITE setRepairTimeout NOTIFY repairTimeoutChanged)

		Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

		Q_PROPERTY(QString status READ status NOTIFY statusChanged)

		Q_PROPERTY(cutehmi::services::StateInterface * states READ states CONSTANT)

		Q_PROPERTY(QQmlListProperty<cutehmi::services::AbstractServiceController> defaultControllers READ defaultControllerList CONSTANT)

		//<CuteHMI.Services-6.workaround target="Qt5" cause="missing">
		// Instead of:
		// QML_LIST_PROPERTY_ASSIGN_BEHAVIOR_REPLACE
		// Some workaround code in AbstractService::ControllerListAppend() is provided.
		//</CuteHMI.Services-6.workaround>
		Q_PROPERTY(QQmlListProperty<cutehmi::services::AbstractServiceController> controllers READ controllerList CONSTANT)

		~AbstractService() override;

		int shutdownTimeout() const;

		/**
		 * Set shutdown timeout.
		 * @param shutdownTimeout time limit [milliseconds] to wait for the service to shutdown itself. If service can not reach
		 * @p stopped nor even @p interrupted state by this time, it will be killed. This can happen if its state interface
		 * implementation is entirely broken.
		 */
		void setShutdownTimeout(int shutdownTimeout);

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
		 * Get state interface.
		 *
		 * @return state interface.
		 */
		cutehmi::services::StateInterface * states() const;

		QQmlListProperty<cutehmi::services::AbstractServiceController> defaultControllerList();

		QQmlListProperty<cutehmi::services::AbstractServiceController> controllerList();

		Q_INVOKABLE void appendController(cutehmi::services::AbstractServiceController * controller);

		Q_INVOKABLE void clearControllers();

	public slots:
		void start();

		void stop();

		void activate();

	signals:
		void stopTimeoutChanged();

		void startTimeoutChanged();

		void repairTimeoutChanged();

		void shutdownTimeoutChanged();

		void nameChanged();

		void statusChanged();

		void started();

		void stopped();

		void activated();

		/**
		 * This signal is emitted, when service has performed all the initialization tasks and it is ready to be started. After this
		 * signal has been emitted a service should respond to start() slot.
		 */
		void initialized();

	protected:
		typedef QList<AbstractServiceController *> ControllersContainer;

		/**
		 * Constructor.
		 * @param stateInterface state interface. Abstract service will take ownership of this object by explicitly setting itself
		 * as its parent. This object is exposed as @ref states property.
		 * @param status initial service status.
		 * @param defaultControllers default controllers.
		 * @param parent parent object.
		 */
		AbstractService(StateInterface * stateInterface, const QString & status, QObject * parent = nullptr, const ControllersContainer * defaultControllers = & DefaultControllers());

		static const ControllersContainer & DefaultControllers();

		const ControllersContainer & controllers() const;

		ControllersContainer & controllers();

	protected slots:
		void setStatus(const QString & status);

	private:
		//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
		static workarounds::qt5compatibility::sizeType ControllerListCount(QQmlListProperty<AbstractServiceController> * property);

		static AbstractServiceController * ControllerListAt(QQmlListProperty<AbstractServiceController> * property, workarounds::qt5compatibility::sizeType index);
		//</CuteHMI.DataAcquisition-2.workaround target="Qt" cause="Qt5">

		static void ControllerListClear(QQmlListProperty<AbstractServiceController> * property);

		static void ControllerListAppend(QQmlListProperty<AbstractServiceController> * property, AbstractServiceController * value);

		//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
		static workarounds::qt5compatibility::sizeType DefaultControllerListCount(QQmlListProperty<AbstractServiceController> * property);

		static AbstractServiceController * DefaultControllerListAt(QQmlListProperty<AbstractServiceController> * property, workarounds::qt5compatibility::sizeType index);
		//</CuteHMI.DataAcquisition-2.workaround target="Qt" cause="Qt5">

		const ControllersContainer * defaultControllerListData() const;

		struct Members {
			int stopTimeout = INITIAL_STOP_TIMEOUT;
			int startTimeout = INITIAL_START_TIMEOUT;
			int repairTimeout = INITIAL_REPAIR_TIMEOUT;
			int shutdownTimeout = INITIAL_SHUTDOWN_TIMEOUT;
			QString name = INITIAL_NAME;
			QString status;
			StateInterface * stateInterface;
			ControllersContainer controllers;
			QQmlListProperty<AbstractServiceController> controllerList;
			QQmlListProperty<AbstractServiceController> defaultControllerList;

			Members(AbstractService * p_parent, StateInterface * p_stateInterface, const QString & p_status, const ControllersContainer * p_defaultControllers):
				status(p_status),
				stateInterface(p_stateInterface),
				controllerList(p_parent, & controllers, & AbstractService::ControllerListAppend, & AbstractService::ControllerListCount, & AbstractService::ControllerListAt, & AbstractService::ControllerListClear),
				defaultControllerList(p_parent, const_cast<ControllersContainer *>(p_defaultControllers), & AbstractService::DefaultControllerListCount, & AbstractService::DefaultControllerListAt)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)C: Copyright © 2022-2023, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
