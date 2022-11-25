#include <cutehmi/services/AbstractService.hpp>
#include <cutehmi/services/ServiceDependency.hpp>
#include <cutehmi/services/ServiceGroup.hpp>

namespace cutehmi {
namespace services {

ServiceDependency::ServiceDependency(QObject * parent):
	ServiceGroupRule(parent),
	m(new Members(this))
{
}

void ServiceDependency::setService(AbstractService * service)
{
	if (m->service != service) {
		m->service = service;
		emit serviceChanged();
	}
}

AbstractService * ServiceDependency::service() const
{
	return m->service;
}

QQmlListProperty<AbstractService> ServiceDependency::requiredServiceList()
{
	return m->requiredServiceList;
}

void ServiceDependency::appendRequiredService(AbstractService * service)
{
	RequiredServiceListAppend(& m->requiredServiceList, service);
}

void ServiceDependency::clearRequiredServices()
{
	RequiredServiceListClear(& m->requiredServiceList);
}

std::unique_ptr<QAbstractTransition> ServiceDependency::conditionalTransition(SlotType type, const AbstractService * service)
{
	switch (type) {
		case SERVICE_START:
			if (service == m->service)
				return std::unique_ptr<QAbstractTransition>(new StartConditionTransition(this));
			break;
		case SERVICE_STOP:
			if (m->requiredServices.contains(const_cast<AbstractService *>(service)))
				return std::unique_ptr<QAbstractTransition>(new StopConditionTransition(this));
			break;
		default:
			return nullptr;
	}

	return nullptr;
}

const ServiceDependency::RequiredServicesContainer & ServiceDependency::requiredServices() const
{
	return m->requiredServices;
}

ServiceDependency::RequiredServicesContainer & ServiceDependency::requiredServices()
{
	return m->requiredServices;
}

workarounds::qt5compatibility::sizeType ServiceDependency::RequiredServiceListCount(QQmlListProperty<AbstractService> * property)
{
	return static_cast<RequiredServicesContainer *>(property->data)->count();
}

AbstractService * ServiceDependency::RequiredServiceListAt(QQmlListProperty<AbstractService> * property, workarounds::qt5compatibility::sizeType index)
{
	return static_cast<RequiredServicesContainer *>(property->data)->value(index);
}

void ServiceDependency::RequiredServiceListClear(QQmlListProperty<AbstractService> * property)
{
	static_cast<RequiredServicesContainer *>(property->data)->clear();
}

void ServiceDependency::RequiredServiceListAppend(QQmlListProperty<AbstractService> * property, AbstractService * value)
{
	static_cast<RequiredServicesContainer *>(property->data)->append(value);
}

ServiceDependency::StartConditionTransition::StartConditionTransition(QPointer<ServiceDependency> serviceDependency):
	m(new Members{
	serviceDependency})
{
	if (m->serviceDependency)
		for (auto && requiredService : m->serviceDependency->requiredServices()) {
			connect(requiredService->states()->started(), & QState::entered, this, [this]() {
				ServiceGroup::PostConditionCheckEvent(machine());
			});
		}
}

bool ServiceDependency::StartConditionTransition::eventTest(QEvent * event)
{
	if (event->type() == static_cast<QEvent::Type>(ServiceGroup::CONDITION_CHECK_EVENT)) {
		if (m->serviceDependency)
			for (auto && requiredService : m->serviceDependency->requiredServices())
				if (!requiredService->states()->started()->active())
					return false;

		return true;
	}

	return QSignalTransition::event(event);
}

ServiceDependency::StopConditionTransition::StopConditionTransition(QPointer<ServiceDependency> serviceDependency):
	m(new Members{
	serviceDependency})
{
	if (m->serviceDependency) {
		connect(m->serviceDependency->service()->states()->stopped(), & QState::entered, this, [this]() {
			ServiceGroup::PostConditionCheckEvent(machine());
		});
		connect(m->serviceDependency->service()->states()->interrupted(), & QState::entered, this, [this]() {
			ServiceGroup::PostConditionCheckEvent(machine());
		});
	}
}

bool ServiceDependency::StopConditionTransition::eventTest(QEvent * event)
{
	if (event->type() == static_cast<QEvent::Type>(ServiceGroup::CONDITION_CHECK_EVENT)) {
		if (m->serviceDependency)
			return m->serviceDependency->service()->states()->stopped()->active()
					|| m->serviceDependency->service()->states()->interrupted()->active();

		return true;
	}

	return QSignalTransition::event(event);
}

}
}

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
