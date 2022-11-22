#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_SERVICEGROUP_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_SERVICEGROUP_HPP

#include "internal/common.hpp"

#include "Service.hpp"
#include "Serviceable.hpp"
#include "ServiceGroupRule.hpp"

//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
#include <cutehmi/workarounds/qt5compatibility/qsizetype.hpp>
//</CuteHMI.Workarounds.Qt5Compatibility-1.workaround>

#include <QQmlEngine>
#include <QQmlListProperty>

namespace cutehmi {
namespace services {

/**
 * Service group.
 *
 * Service group allows to collectively manage a group of services. By its most basic principle, whenever any of
 * start(), stop() or activate() slots is called on the group it forwards the call to the services managed by it. This basic behavior
 * can be customized by using rules.
 *
 * Service group is a service by itself, so it makes use of the state machine to handle propagation of slot calls. Internally for
 * each service it creates substates in its own states configured via Serviceable interface. These substates are executed in
 * parallel, so for example all services will be started at once. However if service group rule can be applied to a particular
 * service then additional subsequent states are added to the substate dedicated to a particular service and rule defines the
 * transition between them.
 */
class CUTEHMI_SERVICES_API ServiceGroup:
	public cutehmi::services::AbstractService,
	public QQmlParserStatus,
	public Serviceable
{
		Q_OBJECT
		QML_NAMED_ELEMENT(ServiceGroup)
		Q_INTERFACES(QQmlParserStatus)

	public:
		enum EventType {
			CONDITION_CHECK_EVENT = QEvent::User + 1,
			SUBCLASS_EVENT
		};

		Q_PROPERTY(int startedCount READ startedCount NOTIFY startedCountChanged)

		Q_PROPERTY(int startingCount READ startingCount NOTIFY startingCountChanged)

		Q_PROPERTY(int stoppingCount READ stoppingCount NOTIFY stoppingCountChanged)

		Q_PROPERTY(int stoppedCount READ stoppedCount NOTIFY stoppedCountChanged)

		Q_PROPERTY(int brokenCount READ brokenCount NOTIFY brokenCountChanged)

		Q_PROPERTY(int repairingCount READ repairingCount NOTIFY repairingCountChanged)

		Q_PROPERTY(int evacuatingCount READ evacuatingCount NOTIFY evacuatingCountChanged)

		Q_PROPERTY(int interruptedCount READ interruptedCount NOTIFY interruptedCountChanged)

		Q_PROPERTY(int activeCount READ activeCount NOTIFY activeCountChanged)

		Q_PROPERTY(int yieldingCount READ yieldingCount NOTIFY yieldingCountChanged)

		Q_PROPERTY(int idlingCount READ idlingCount NOTIFY idlingCountChanged)

		Q_PROPERTY(QQmlListProperty<cutehmi::services::ServiceGroupRule> rules READ ruleList CONSTANT)

		Q_PROPERTY(QQmlListProperty<cutehmi::services::AbstractService> services READ serviceList CONSTANT)
		Q_CLASSINFO("DefaultProperty", "services")

		static void PostConditionCheckEvent(QStateMachine * stateMachine);

		explicit ServiceGroup(QObject * parent = nullptr);

		~ServiceGroup() override;

		int startedCount() const;

		int startingCount() const;

		int stoppingCount() const;

		int stoppedCount() const;

		int brokenCount() const;

		int repairingCount() const;

		int evacuatingCount() const;

		int interruptedCount() const;

		int activeCount() const;

		int yieldingCount() const;

		int idlingCount() const;

		QQmlListProperty<cutehmi::services::ServiceGroupRule> ruleList();

		Q_INVOKABLE void appendRule(cutehmi::services::ServiceGroupRule * rule);

		Q_INVOKABLE void clearRules();

		QQmlListProperty<cutehmi::services::AbstractService> serviceList();

		Q_INVOKABLE void appendService(cutehmi::services::AbstractService * service);

		Q_INVOKABLE void clearServices();

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

		void classBegin() override;

		void componentComplete() override;

	public slots:
		void postConditionCheckEvent() const;

	signals:
		void startedCountChanged();

		void startingCountChanged();

		void stoppingCountChanged();

		void stoppedCountChanged();

		void brokenCountChanged();

		void repairingCountChanged();

		void evacuatingCountChanged();

		void interruptedCountChanged();

		void activeCountChanged();

		void yieldingCountChanged();

		void idlingCountChanged();

	protected:
		typedef QList<ServiceGroupRule *> RulesContainer;

		typedef QList<AbstractService *> ServicesContainer;

		static const ControllersContainer & DefaultControllers();

		void setStartedCount(int count);

		void setStartingCount(int count);

		void setStoppingCount(int count);

		void setStoppedCount(int count);

		void setBrokenCount(int count);

		void setRepairingCount(int count);

		void setEvacuatingCount(int count);

		void setInterruptedCount(int count);

		void setActiveCount(int count);

		void setYieldingCount(int count);

		void setIdlingCount(int count);

		const RulesContainer & rules() const;

		RulesContainer & rules();

		const ServicesContainer & services() const;

		ServicesContainer & services();

		Q_SIGNAL void groupBroken();

		Q_SIGNAL void groupStarted();

		Q_SIGNAL void groupStopped();

	protected slots:
		void handleCounters();

	private:
		typedef QList<QMetaObject::Connection> ConnectionsContainer;

		struct ConnectionData {
			ConnectionsContainer stopped;
			ConnectionsContainer starting;
			ConnectionsContainer started;
			ConnectionsContainer stopping;
			ConnectionsContainer broken;
			ConnectionsContainer repairing;
			ConnectionsContainer evacuating;
			ConnectionsContainer interrupted;
			ConnectionsContainer yielding;
			ConnectionsContainer active;
			ConnectionsContainer idling;
			ConnectionsContainer stateChanged;
		};

		typedef QHash<AbstractService *, ConnectionData *> ServiceConnectionsContainer;

		static QString & DefaultStatus();

		//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
		static workarounds::qt5compatibility::sizeType RuleListCount(QQmlListProperty<ServiceGroupRule> * property);

		static ServiceGroupRule * RuleListAt(QQmlListProperty<ServiceGroupRule> * property, workarounds::qt5compatibility::sizeType index);
		//</CuteHMI.DataAcquisition-2.workaround target="Qt" cause="Qt5">

		static void RuleListClear(QQmlListProperty<ServiceGroupRule> * property);

		static void RuleListAppend(QQmlListProperty<ServiceGroupRule> * property, ServiceGroupRule * value);

		//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
		static workarounds::qt5compatibility::sizeType ServiceListCount(QQmlListProperty<AbstractService> * property);

		static AbstractService * ServiceListAt(QQmlListProperty<AbstractService> * property, workarounds::qt5compatibility::sizeType index);
		//</CuteHMI.DataAcquisition-2.workaround target="Qt" cause="Qt5">

		static void ServiceListClear(QQmlListProperty<AbstractService> * property);

		static void ServiceListAppend(QQmlListProperty<AbstractService> * property, AbstractService * value);

		static void ConnectStateCounters(ConnectionData & connectionData, ServiceGroup * serviceGroup, AbstractService * service);

		static void ReconnectStateCounter(ServiceGroup * serviceGroup, ConnectionsContainer & connections, int (ServiceGroup::*getter)() const, void (ServiceGroup::*setter)(int), const QAbstractState & state);

		static void ClearConnections(ConnectionsContainer & connections);

		static ConnectionData * CreateConnectionDataEntry(ServiceConnectionsContainer & serviceConnections, AbstractService * service);

		static void DeleteConnectionDataEntry(ServiceConnectionsContainer & serviceConnections, AbstractService * service);

		internal::ServiceStateInterface * stateInterface() const;

		void initializeStateMachine(bool start = true);

		void destroyStateMachine();

		void configureStoppingOrEvacuating(QState * state, AssignStatusFunction assignStatus);

		void configureStartingOrRepairing(QState * state, AssignStatusFunction assignStatus);

		struct Members {
			RulesContainer rules;
			QQmlListProperty<ServiceGroupRule> ruleList;
			ServicesContainer services;
			QQmlListProperty<AbstractService> serviceList;
			ServiceConnectionsContainer serviceConnections;
			int stoppedCount;
			int startingCount;
			int startedCount;
			int stoppingCount;
			int brokenCount;
			int repairingCount;
			int evacuatingCount;
			int interruptedCount;
			int yieldingCount;
			int activeCount;
			int idlingCount;
			bool qmlBeingParsed;
			internal::ServiceStateMachine * stateMachine;

			Members(ServiceGroup * p_parent):
				ruleList(p_parent, & rules, & ServiceGroup::RuleListAppend, & ServiceGroup::RuleListCount, & ServiceGroup::RuleListAt, & ServiceGroup::RuleListClear),
				serviceList(p_parent, & services, & ServiceGroup::ServiceListAppend, & ServiceGroup::ServiceListCount, & ServiceGroup::ServiceListAt, & ServiceGroup::ServiceListClear),
				stoppedCount(0),
				startingCount(0),
				startedCount(0),
				stoppingCount(0),
				brokenCount(0),
				repairingCount(0),
				evacuatingCount(0),
				interruptedCount(0),
				yieldingCount(0),
				activeCount(0),
				idlingCount(0),
				qmlBeingParsed(false),
				stateMachine(nullptr)
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
