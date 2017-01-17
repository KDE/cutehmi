#include "CuteHMIBaseQMLPlugin.hpp"

#include <base/ServiceRegistry.hpp>

#include <QtQml>

void CuteHMIBaseQMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.Base"));

	qmlRegisterType<cutehmi::base::Service>(uri, 1, 0, "Service");
	qmlRegisterSingletonType<cutehmi::base::ServiceRegistry>(uri, 1, 0, "ServiceRegistry", ServiceRegistryProvider);
}

QObject * CuteHMIBaseQMLPlugin::ServiceRegistryProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
{
	Q_UNUSED(scriptEngine)

	cutehmi::base::ServiceRegistry * serviceRegistry = & cutehmi::base::ServiceRegistry::Instance();
	engine->setObjectOwnership(serviceRegistry, QQmlEngine::CppOwnership);
	return serviceRegistry;
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
