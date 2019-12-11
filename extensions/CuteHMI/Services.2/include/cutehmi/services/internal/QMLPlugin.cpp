#include "QMLPlugin.hpp"

#include <cutehmi/services/Service.hpp>
#include <cutehmi/services/PollingTimer.hpp>
#include <cutehmi/services/ServiceManager.hpp>

#include <QtQml>

namespace cutehmi {
namespace services {
namespace internal {

void QMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.Services"));

	qmlRegisterType<cutehmi::services::Service>(uri, CUTEHMI_SERVICES_MAJOR, 0, "Service");
	qmlRegisterType<cutehmi::services::PollingTimer>(uri, CUTEHMI_SERVICES_MAJOR, 0, "PollingController");
	qmlRegisterSingletonType<cutehmi::services::ServiceManager>(uri, CUTEHMI_SERVICES_MAJOR, 0, "ServiceManager", ServiceManagerProvider);
}

QObject * QMLPlugin::ServiceManagerProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	cutehmi::services::ServiceManager * serviceManager = & cutehmi::services::ServiceManager::Instance();
	engine->setObjectOwnership(serviceManager, QQmlEngine::CppOwnership);
	return serviceManager;
}

}
}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
