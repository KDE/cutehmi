#ifndef H_MODULES_CUTEHMI_u_TERMOBOT_u_1_SRC_CUTEHMI_TERMOBOT_DATABASECONNECTIONDATA_HPP
#define H_MODULES_CUTEHMI_u_TERMOBOT_u_1_SRC_CUTEHMI_TERMOBOT_DATABASECONNECTIONDATA_HPP

#include <QString>

namespace cutehmi {
namespace termobot {

struct DatabaseConnectionData
{
    QString type;
    QString connectionName;
    QString hostName;
    int port;
    QString databaseName;
    QString userName;
    QString password;
};

}
}

#endif

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
