#ifndef H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_SERVICEDEPENDENCY_HPP
#define H_EXTENSIONS_CUTEHMI_SERVICES_3_INCLUDE_CUTEHMI_SERVICES_SERVICEDEPENDENCY_HPP

#include "internal/common.hpp"
#include "ServiceGroupRule.hpp"

//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
#include <cutehmi/workarounds/qt5compatibility/qsizetype.hpp>
//</CuteHMI.Workarounds.Qt5Compatibility-1.workaround>

#include <QPointer>
#include <QSignalTransition>
#include <QQmlEngine>
#include <QQmlListProperty>

namespace cutehmi {
namespace services {

class AbstractService;

class CUTEHMI_SERVICES_API ServiceDependency:
	public ServiceGroupRule
{
		Q_OBJECT
		QML_NAMED_ELEMENT(ServiceDependency)

	public:
		Q_PROPERTY(cutehmi::services::AbstractService * service READ service WRITE setService NOTIFY serviceChanged)

		Q_PROPERTY(QQmlListProperty<cutehmi::services::AbstractService> requires READ requiredServiceList CONSTANT)

		ServiceDependency(QObject * parent = nullptr);

		void setService(AbstractService * service);

		cutehmi::services::AbstractService * service() const;

		QQmlListProperty<cutehmi::services::AbstractService> requiredServiceList();

		Q_INVOKABLE void appendRequiredService(cutehmi::services::AbstractService * service);

		Q_INVOKABLE void clearRequiredServices();

		std::unique_ptr<QAbstractTransition> conditionalTransition(SlotType type, const AbstractService * service) override;

	signals:
		void serviceChanged();

	protected:
		typedef QList<AbstractService *> RequiredServicesContainer;

		const RequiredServicesContainer & requiredServices() const;

		RequiredServicesContainer & requiredServices();

	private:
		class StartConditionTransition: public QSignalTransition {
			public:
				StartConditionTransition(QPointer<ServiceDependency> serviceDependency);

			protected:
				bool eventTest(QEvent * event) override;

			private:
				struct Members {
					QPointer<ServiceDependency> serviceDependency;
				};

				MPtr<Members> m;
		};

		class StopConditionTransition: public QSignalTransition {
			public:
				StopConditionTransition(QPointer<ServiceDependency> serviceDependency);

			protected:
				bool eventTest(QEvent * event) override;

			private:
				struct Members {
					QPointer<ServiceDependency> serviceDependency;
				};

				MPtr<Members> m;
		};

		//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">
		static workarounds::qt5compatibility::sizeType RequiredServiceListCount(QQmlListProperty<AbstractService> * property);

		static AbstractService * RequiredServiceListAt(QQmlListProperty<AbstractService> * property, workarounds::qt5compatibility::sizeType index);
		//</CuteHMI.DataAcquisition-2.workaround target="Qt" cause="Qt5">

		static void RequiredServiceListClear(QQmlListProperty<AbstractService> * property);

		static void RequiredServiceListAppend(QQmlListProperty<AbstractService> * property, AbstractService * value);

		struct Members
		{
			AbstractService * service = nullptr;
			RequiredServicesContainer requiredServices;
			QQmlListProperty<AbstractService> requiredServiceList;

			Members(ServiceDependency * p_parent):
				requiredServiceList(p_parent, & requiredServices, & ServiceDependency::RequiredServiceListAppend, & ServiceDependency::RequiredServiceListCount, & ServiceDependency::RequiredServiceListAt, & ServiceDependency::RequiredServiceListClear)
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
