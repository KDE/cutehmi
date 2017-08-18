#include "CuteHMIAuthSSHQMLPlugin.hpp"

//#include <authssh/Auth.hpp>

#include <QtQml>

void CuteHMIAuthSSHQMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.AuthSSH"));

//  qmlRegisterType<cutehmi::authssh::Auth>(uri, 1, 0, "Auth");
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
