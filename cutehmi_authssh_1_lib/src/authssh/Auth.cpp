#include "../../include/authssh/Auth.hpp"

namespace cutehmi {
namespace authssh {

QString Auth::user() const
{
	return m->user;
}

bool Auth::login(const QString & user, const QString & password)
{
	if ((user == "dupa") &&  (password == "dupa")) {
		setUser("dupa");
		return true;
	}
	setUser("");
	return false;
}

void Auth::logout()
{
}

void Auth::setUser(const QString & user)
{
	if (m->user != user) {
		m->user = user;
		emit userChanged();
	}
}

Auth::Auth(QObject * parent):
	QObject(parent),
	m(new Members)
{
}


}
}

//(c)MPWZ: Copyright © 2017, Michal Policht, Wojciech Zygmuntowicz. All rights reserved.
//(c)MPWZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
