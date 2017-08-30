#include "../../include/authssh/Auth.hpp"

namespace cutehmi {
namespace authssh {

Auth::Auth(QObject * parent):
	QObject(parent)
{
}

void Auth::login(const QString & user, const QString & password)
{
}

void Auth::logout()
{
}

}
}

//(c)MPWZ: Copyright © 2017, Michal Policht, Wojciech Zygmuntowicz. All rights reserved.
//(c)MPWZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
