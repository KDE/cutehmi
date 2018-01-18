#include "../../include/authssh/Session.hpp"
#include "../../include/authssh/Exception.hpp"

#include <base/ErrorException.hpp>

#include <QSocketNotifier>	//temp

namespace cutehmi {
namespace authssh {

QString Session::Error::str() const
{
	switch (code()) {
		case Error::FAILED_GET_PUBLIC_KEY:
			return tr("Failed to get public key.");
		case Error::FAILED_GET_PUBLIC_KEY_HASH:
			return tr("Failed to get public key hash.");
		case Error::FAILED_PUBLIC_KEY_HEX_STRING:
			return tr("Failed to convert public key hash to a hex string.");
		case Error::ALREADY_CONNNECTED:
			return tr("Client already connected.");
		case Error::COULD_NOT_CONNECT:
			return tr("Client could not connect with host.");
		default:
			return base::Error::str();
	}
}

const int Session::INITIAL_LIBSSH_VERBOSITY;

Session::Session(const QString & host, uint port, const QString & user, QObject * parent) noexcept(false):
	QObject(parent),
	m(new Members(host, port, user))
{
	m->session = ssh_new();
	if (!m->session)
		throw Exception(tr("Could not allocate session."));

	ssh_options_set(m->session, SSH_OPTIONS_LOG_VERBOSITY, & INITIAL_LIBSSH_VERBOSITY);
	ssh_options_set(m->session, SSH_OPTIONS_HOST, host.toLocal8Bit().constData());
	ssh_options_set(m->session, SSH_OPTIONS_PORT, & port);
	ssh_options_set(m->session, SSH_OPTIONS_USER, user.toLocal8Bit().constData());
}

Session::~Session()
{
	if (connected())
		disconnect();

	// Destroy session.
	ssh_free(m->session);
}

QString Session::host() const
{
	return m->host;
}

uint Session::port() const
{
	return m->port;
}

QString Session::user() const
{
	return m->user;
}

bool Session::connected() const
{
	//<workaround id="cutehmi_authssh_1_lib-1" target="libssh" cause="bug">
	// Function 'ssh_is_connected()' returns true, even if 'ssh_connect()' fails to establish connection due to	timeout.
	// return ssh_is_connected(session());
	return m->connected;
	//</workaround>
}

std::pair<Session::Error, QString> Session::getServerKey()
{
	CUTEHMI_UTILS_DEBUG("Getting server key...");

	Error error = Error::OK;
	ssh_key pubkey;

	if (m->serverKeyCache.isEmpty()) {
		int sshGetPublickeyResult = ssh_get_publickey(session(), & pubkey);
		if (sshGetPublickeyResult == SSH_OK) {
			std::size_t hashSize;
			unsigned char * hash = NULL;
			if (ssh_get_publickey_hash(pubkey, SSH_PUBLICKEY_HASH_SHA1, & hash, & hashSize) == 0) {
				char * hexHash = ssh_get_hexa(hash, hashSize);
				if (hexHash != NULL) {
					m->serverKeyCache = hexHash;
					ssh_string_free_char(hexHash);
				} else {
					CUTEHMI_UTILS_WARNING("Function 'ssh_get_hexa()' has failed.");
					error = Error::FAILED_PUBLIC_KEY_HEX_STRING;
				}
				ssh_clean_pubkey_hash(& hash);
			} else {
				CUTEHMI_UTILS_WARNING("Function 'ssh_get_publickey_hash()' has failed.");
				error = Error::FAILED_GET_PUBLIC_KEY_HASH;
			}
			ssh_key_free(pubkey);
		} else {
			CUTEHMI_UTILS_WARNING("Function 'ssh_get_publickey()' has failed due to following error (code: " << sshGetPublickeyResult << "): " << ssh_get_error(session()) << ".");
			error = Error::FAILED_GET_PUBLIC_KEY;
		}
	}

	return std::make_pair(error, m->serverKeyCache);
}

Session::Error Session::connect()
{
	CUTEHMI_UTILS_DEBUG("Connecting to host '" << m->host << ":" << m->port << "'...");

	if (connected()) {
		CUTEHMI_UTILS_WARNING("Already connected.");
		return Error::ALREADY_CONNNECTED;
	}

	int result = SSH_AGAIN;
	while (result == SSH_AGAIN)
		result = ssh_connect(session());
	if (result != SSH_OK) {
		CUTEHMI_UTILS_WARNING("Could not connect to host '" << m->host << "' on port '" << m->port << "', because of the following error: " << ssh_get_error(session()) << ".");
	//<workaround ref="cutehmi_authssh_1_lib-1" target="libssh" cause="bug">
		setConnected(false);
	} else {
		setConnected(true);
	//</workaround>
		CUTEHMI_UTILS_DEBUG("Connected with host '" << m->host << "' using port '" << m->port << "'.");
		CUTEHMI_UTILS_DEBUG("Supported authentication methods: " << authMethods().join(", ") << ".");
		return Error::OK;
	}
	return Error::COULD_NOT_CONNECT;
}

void Session::disconnect()
{
	if (!connected()) {
		CUTEHMI_UTILS_WARNING("Client already disconnected.");
		return;
	}

	//<workaround ref="cutehmi_authssh_1_lib-1" target="libssh" cause="bug">
	setConnected(false);
	//</workaround>

	ssh_disconnect(session());
}

bool Session::passwordAuth(const QString & password)
{
	CUTEHMI_UTILS_DEBUG("Authenticating user with password...");

	int result = ssh_userauth_password(session(), NULL, password.toLocal8Bit().constData());
	if (result == SSH_AUTH_SUCCESS)
		return true;
	else
		CUTEHMI_UTILS_WARNING("Function 'ssh_userauth_password()' has failed due to following error (code: " << result << "): " << ssh_get_error(session()) << " .");
	return false;
}

ssh_session Session::session() const
{
	CUTEHMI_UTILS_ASSERT(m->session != NULL, "attempt to use NULL session (either uninitialized or acquired)");

	return m->session;
}


//<workaround ref="cutehmi_authssh_1_lib-1" target="libssh" cause="bug">
void Session::setConnected(bool connected)
{
	m->connected = connected;
}
//</workaround>

ssh_session Session::acquireLibsshSession()
{
	return m->session;
}

void Session::releaseLibsshSession(ssh_session session)
{
	m->session = session;
}

QStringList Session::authMethods() const
{
	int methods;
	QStringList methodList;

	ssh_userauth_none(session(), NULL);	// See below.
	methods = ssh_userauth_list(session(), NULL); // "This requires the function ssh_userauth_none() to be called before the methods are available. The server MAY return a list of methods that may continue." -- http://api.libssh.org/master/group__libssh__auth.html#ga35d44897a44b4bb3b7c01108c1812a37
	if (methods == 0)
		return QStringList("[could not obtain authentication methods from server]");

	auto checkFlag = [& methodList, & methods](int flag, QString methodName) {
		if (methods & flag) {
			methodList << methodName;
			methods &= ~flag;
		}
	};
	checkFlag(SSH_AUTH_METHOD_NONE, "none");
	checkFlag(SSH_AUTH_METHOD_PUBLICKEY, "public key");
	checkFlag(SSH_AUTH_METHOD_INTERACTIVE, "interactive");
	checkFlag(SSH_AUTH_METHOD_PASSWORD, "password");

	int flagShift = 0;
	while ((methods >> flagShift) > 0) {
		if (methods & (0x1 << flagShift))
			methodList << QString("unrecognized method (0x") + QString::number(0x1 << flagShift, 16) + ")";
		flagShift++;
	}

	return methodList;
}

}
}

//(c)MPWZ: Copyright © 2018, Michal Policht, Wojciech Zygmuntowicz. All rights reserved.
//(c)MPWZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
