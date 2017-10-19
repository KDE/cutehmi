#include "../../include/authssh/Auth.hpp"
#include "../../include/authssh/Exception.hpp"

#include <base/Prompt.hpp>

namespace cutehmi {
namespace authssh {

Auth::Auth(QObject * parent):
	QObject(parent),
	m(new Members)
{
	m->settings.beginGroup("cutehmi_authssh_1_lib");
}

bool Auth::authenticated() const
{
	return m->authenticated;
}

const Client * Auth::client() const
{
	return & m->client;
}

Client * Auth::client()
{
	return & m->client;
}

bool Auth::login(const QString & user, const QString & password)
{
	if (authenticated())
		logout();

	client()->setUser(user);

	CUTEHMI_AUTHSSH_QDEBUG("Logging in user '" << client()->user() << "'.");
	try {
		client()->newSession();
		client()->connect();
		QString hostKey = m->settings.value(hostKeySettingsKey()).toString();
		if (hostKey.isEmpty())
			emit hostKeyNew();
		else if (client()->hostKey() != hostKey)
			emit hostKeyMismatch();
		else if (client()->passwordAuth(password)) {
			setAuthenticated(true);
			return true;
		}
	} catch (const Exception & e) {
		base::Prompt::Critical(e.what());
	}

	logout();
	return false;
}

void Auth::logout()
{
	setAuthenticated(false);
	if (client()->hasSession()) {
		if (client()->connected())
			client()->disconnect();
		client()->destroySession();
	}
	CUTEHMI_AUTHSSH_QDEBUG("Logged out.");
}

void Auth::acceptHostKey()
{
	m->settings.setValue(hostKeySettingsKey(), client()->hostKey());
}

void Auth::setAuthenticated(bool authenticated)
{
	if (m->authenticated != authenticated) {
		m->authenticated = authenticated;
		emit authenticatedChanged();
	}
}

QString Auth::hostKeySettingsKey() const
{
	return QString("hostKey/") + client()->host() + "/" + QString::number(client()->port());
}

}
}

//(c)MPWZ: Copyright © 2017, Michal Policht, Wojciech Zygmuntowicz. All rights reserved.
//(c)MPWZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
