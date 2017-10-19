#include "../../include/authssh/Client.hpp"
#include "../../include/authssh/Exception.hpp"

#include <base/ErrorException.hpp>

namespace cutehmi {
namespace authssh {

QString Client::Error::str() const
{
	switch (code()) {
		case Error::FAILED_GET_PUBLIC_KEY:
			return tr("Failed to get public key.");
		case Error::FAILED_GET_PUBLIC_KEY_HASH:
			return tr("Failed to get public key hash.");
		case Error::FAILED_PUBLIC_KEY_HEX_STRING:
			return tr("Failed to convert public key hash to a hex string.");
		default:
			return base::Error::str();
	}
}

const int Client::INITIAL_VERBOSITY;

Client::Client(QObject * parent):
	QObject(parent),
	m(new Members{INITIAL_HOST, INITIAL_PORT, INITIAL_USER, QString(), 0, false})
{
}

Client::~Client()
{
	if (connected())
		disconnect();
	if (hasSession())
		destroySession();
}

QString Client::host() const
{
	return m->host;
}

void Client::setHost(const QString & host)
{
	if (m->host != host) {
		m->host = host;
		emit hostChanged();
	}
}

int Client::port() const
{
	return m->port;
}

void Client::setPort(int port)
{
	if (m->port != port) {
		m->port = port;
		emit portChanged();
	}
}

QString Client::user() const
{
	return m->user;
}

void Client::setUser(const QString & user)
{
	if (m->user != user) {
		m->user = user;
		emit userChanged();
	}
}

bool Client::connected() const
{
	//<workaround id="cutehmi_authssh_1_lib-1" target="libssh" cause="bug">
	// Function 'ssh_is_connected()' returns true, even if 'ssh_connect()' fails to establish connection due to	timeout.
	// return ssh_is_connected(session());
	return m->connected;
	//</workaround>
}

QString Client::hostKey() const
{
	return m->hostKey;
}

void Client::newSession()
{
	CUTEHMI_BASE_ASSERT(m->session == 0, "memory leak - old session must be destroyed with destroySession() function");

	m->session = ssh_new();
	if (!m->session)
		throw Exception(tr("Could not allocate session."));

	ssh_options_set(session(), SSH_OPTIONS_LOG_VERBOSITY, & INITIAL_VERBOSITY);
	ssh_options_set(session(), SSH_OPTIONS_HOST, m->host.toLocal8Bit().constData());
	ssh_options_set(session(), SSH_OPTIONS_PORT, & m->port);
	ssh_options_set(session(), SSH_OPTIONS_USER, m->user.toLocal8Bit().constData());
}

void Client::destroySession()
{
	if (!hasSession()) {
		CUTEHMI_AUTHSSH_QWARNING("Session already destroyed.");
		return;
	}

	ssh_free(m->session);
	m->session = 0;
}

bool Client::hasSession() const
{
	return m->session;
}

void Client::connect()
{
	if (connected()) {
		CUTEHMI_AUTHSSH_QWARNING("Client already connected.");
		return;
	}

	int result = SSH_AGAIN;
	while (result == SSH_AGAIN)
		result = ssh_connect(session());
	if (result != SSH_OK) {
		CUTEHMI_AUTHSSH_QWARNING("Client could not connect with host '" << m->host << "' on port '" << m->port << "', because of the following error: " << ssh_get_error(session()) << ".");
	//<workaround ref="cutehmi_authssh_1_lib-1" target="libssh" cause="bug">
		setConnected(false);
	} else {
		setConnected(true);
	//</workaround>
		CUTEHMI_AUTHSSH_QDEBUG("Client connected with host '" << m->host << "' using port '" << m->port << "'.");
		CUTEHMI_AUTHSSH_QDEBUG("Supported authentication methods: " << authMethods().join(", ") << ".");

		Error hostKeyError = updateHostKey();
		if (hostKeyError != Error::OK)
			throw base::ErrorException(Error(hostKeyError));
	}
}

void Client::disconnect()
{
	if (!connected()) {
		CUTEHMI_AUTHSSH_QWARNING("Client already disconnected.");
		return;
	}

	//<workaround ref="cutehmi_authssh_1_lib-1" target="libssh" cause="bug">
	setConnected(false);
	//</workaround>

	ssh_disconnect(session());
}

bool Client::passwordAuth(const QString & password)
{
	int result = ssh_userauth_password(session(), NULL, password.toLocal8Bit().constData());
	if (result == SSH_AUTH_SUCCESS)
		return true;
	else
		CUTEHMI_AUTHSSH_QWARNING("Function 'ssh_userauth_password()' has failed due to following error (code: " << result << "): " << ssh_get_error(session()) << " .");
	return false;
}

Client::Error Client::updateHostKey()
{
	Error result = Error::OK;
	ssh_key pubkey;

	int sshGetPublickeyResult = ssh_get_publickey(session(), & pubkey);
	if (sshGetPublickeyResult == SSH_OK) {
		std::size_t hashSize;
		unsigned char * hash = NULL;
		if (ssh_get_publickey_hash(pubkey, SSH_PUBLICKEY_HASH_SHA1, & hash, & hashSize) == 0) {
			char * hexHash = ssh_get_hexa(hash, hashSize);
			if (hexHash != NULL) {
				setHostKey(hexHash);
				ssh_string_free_char(hexHash);
			} else {
				CUTEHMI_AUTHSSH_QWARNING("Function 'ssh_get_hexa()' has failed.");
				result = Error::FAILED_PUBLIC_KEY_HEX_STRING;
			}
			ssh_clean_pubkey_hash(& hash);
		} else {
			CUTEHMI_AUTHSSH_QWARNING("Function 'ssh_get_publickey_hash()' has failed.");
			result = Error::FAILED_GET_PUBLIC_KEY_HASH;
		}
		ssh_key_free(pubkey);
	} else {
		CUTEHMI_AUTHSSH_QWARNING("Function 'ssh_get_publickey()' has failed due to following error (code: " << sshGetPublickeyResult << "): " << ssh_get_error(session()) << ".");
		result = Error::FAILED_GET_PUBLIC_KEY;
	}

	return result;
}

void Client::setHostKey(const QString & key)
{
	if (m->hostKey != key) {
		m->hostKey = key;
		emit hostKeyChanged();
	}
}

//<workaround ref="cutehmi_authssh_1_lib-1" target="libssh" cause="bug">
void Client::setConnected(bool connected)
{
	if (m->connected != connected) {
		m->connected = connected;
		emit connectedChanged();
	}
}
//</workaround>

ssh_session Client::session() const
{
	CUTEHMI_BASE_ASSERT(m->session != 0, "attempt to use unallocated session");

	return m->session;
}

QStringList Client::authMethods() const
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

//(c)MPWZ: Copyright © 2017, Michal Policht, Wojciech Zygmuntowicz. All rights reserved.
//(c)MPWZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
