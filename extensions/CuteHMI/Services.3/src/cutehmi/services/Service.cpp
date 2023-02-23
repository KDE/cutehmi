#include "Service.hpp"
#include "internal/ServiceStateMachine.hpp"
#include "internal/ServiceStateInterface.hpp"

#include <cutehmi/Notification.hpp>

#include <QCoreApplication>

namespace cutehmi {
namespace services {

Service::Service(QObject * parent):
	AbstractService(new internal::ServiceStateInterface, DefaultStatus(), parent),
	m(new Members{
	nullptr,
	false})
{
	// Service status is read-only property, thus it is updated through state interface writebale double.
	connect(stateInterface(), & internal::ServiceStateInterface::statusChanged, this, & Service::setStatus);
}

Service::~Service()
{
	stateInterface()->shutdown();
}

void Service::setServiceable(QVariant serviceable)
{
	QObject * qobjectPtr = serviceable.value<QObject *>();
	Serviceable * serviceablePtr = dynamic_cast<Serviceable *>(qobjectPtr);
	if (qobjectPtr != nullptr && serviceablePtr == nullptr)
		CUTEHMI_WARNING("Object assigned as serviceable to '"  << name() << "' service does not implement 'cutehmi::services::Serviceable' interface.");

	if (m->serviceable != serviceablePtr) {
		m->serviceable = serviceablePtr;
		if (!m->qmlBeingParsed)
			configureStateInterface();
		if (!m->serviceable)
			setStatus(DefaultStatus());

		emit serviceableChanged();
	}
}

QVariant Service::serviceable() const
{
	return QVariant::fromValue(m->serviceable);
}

void Service::classBegin()
{
	m->qmlBeingParsed = true;
}

void cutehmi::services::Service::componentComplete()
{
	if (m->qmlBeingParsed && m->serviceable)
		configureStateInterface();

	m->qmlBeingParsed = false;
}

QString & Service::DefaultStatus()
{
	static QString name = QObject::tr("No serviceable object");
	return name;
}

internal::ServiceStateInterface * Service::stateInterface() const
{
	return static_cast<internal::ServiceStateInterface *>(states());
}

void Service::configureStateInterface()
{
	stateInterface()->configureServiceable(m->serviceable);
	emit initialized();
}

}
}

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
