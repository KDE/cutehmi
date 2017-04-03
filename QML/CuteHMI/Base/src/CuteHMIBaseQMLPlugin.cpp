#include "CuteHMIBaseQMLPlugin.hpp"

#include <base/CuteHMI.hpp>

#include <QtQml>

void CuteHMIBaseQMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.Base"));
}

//QObject * CuteHMIBaseQMLPlugin::ServiceRegistryProvider(QQmlEngine * engine, QJSEngine * scriptEngine)
//{
//	Q_UNUSED(scriptEngine)

//	cutehmi::base::ServiceRegistry * serviceRegistry = cutehmi::base::CuteHMI::Instance().project()->serviceRegistry();
//	engine->setObjectOwnership(serviceRegistry, QQmlEngine::CppOwnership);
//	return serviceRegistry;
//}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
