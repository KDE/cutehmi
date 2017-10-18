#ifndef CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_SSHCLIENT_HPP
#define CUTEHMI_CUTEHMI__AUTHSSH__1__LIB_INCLUDE_AUTHSSH_SSHCLIENT_HPP

#include <QObject>

namespace cutehmi {
namespace authssh {

class SSHClient:
	public QObject
{
	Q_OBJECT

	public:
		explicit SSHClient(QObject *parent = nullptr);

	signals:

	public slots:
};

}
}

#endif

//(c)MPWZ: Copyright © 2017, Michal Policht, Wojciech Zygmuntowicz. All rights reserved.
//(c)MPWZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
