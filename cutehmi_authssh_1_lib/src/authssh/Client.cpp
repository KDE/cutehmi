#include "../../include/authssh/Client.hpp"
#include "../../include/authssh/AbstractChannel.hpp"
#include "../../include/authssh/Exception.hpp"

#include <base/Prompt.hpp>

namespace cutehmi {
namespace authssh {

Client::Client(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

Client::~Client()
{
	stopChannels();
}

QString Client::serverHost() const
{
	return m->serverHost;
}

void Client::setServerHost(const QString & host)
{
	if (m->serverHost != host) {
		m->serverHost = host;
		emit serverHostChanged();
	}
}

uint Client::serverPort() const
{
	return m->serverPort;
}

void Client::setServerPort(uint port)
{
	if (m->serverPort != port) {
		m->serverPort = port;
		emit serverPortChanged();
	}
}

QString Client::serverKey() const
{
	return m->serverKey;
}

QString Client::user() const
{
	return m->user;
}

bool Client::authenticated() const
{
	return m->authenticated;
}

void Client::addChannel(std::unique_ptr<AbstractChannel> channel)
{
	connect(channel.get(), & AbstractChannel::error, this, & Client::handleChannelError);
	m->channelsThread.addChannel(std::move(channel));
}

void Client::acceptServerKey()
{
	m->settings.beginGroup(QSETTINGS_GROUP);
	m->settings.setValue(serverKeySettingsKey(), serverKey());
	m->settings.endGroup();
}

void Client::invalidateServerKey()
{
	m->settings.beginGroup(QSETTINGS_GROUP);
	m->settings.remove(serverKeySettingsKey());
	m->settings.endGroup();
}

bool Client::login(const QString & user, const QString & password)
{
	CUTEHMI_UTILS_DEBUG("Logging in user '" << user << "'...");

	try {
		std::unique_ptr<Session> session(new Session(m->serverHost, m->serverPort, user));

		// Connect to server.
		Session::Error connectError = session->connect();
		if (connectError != Session::Error::OK) {
			base::Prompt::Critical(tr("Could not connect to host '%1:%2', because of following error. ").arg(m->serverHost).arg(m->serverPort) + connectError.str());
			return false;
		}

		// Verify server.
		std::pair<Session::Error, QString> serverKeyError = session->getServerKey();
		setServerKey(serverKeyError.second);
		if (!serverKeyError.first)
			return false;
		if (!verifyServer())
			return false;

		// Authenticate.
		if (session->passwordAuth(password)) {
			setUser(user);
			setAuthenticated(true);
			if (m->sessions.isEmpty())
				startChannels(session.get());
//			else
//				m->channelsThread.pushSession(session);
			m->sessions.append(QVariant::fromValue(session.release()));
			return true;
		}
	} catch (const Exception & e) {
		base::Prompt::Critical(e.what());
		return false;
	}

	return false;
}

void Client::logout()
{
	if (Session * session = takeLastSession()) {
		if (m->sessions.isEmpty()) {
			stopChannels();
			setAuthenticated(false);
			setUser(QString());
		} else {
//			m->channelsThread.popSession();
			setServerHost(lastSession()->host());
			setServerPort(lastSession()->port());
			setServerKey(lastSession()->getServerKey().second);
			setUser(lastSession()->user());
		}
		delete session;
		CUTEHMI_UTILS_DEBUG("Logged out.");
	}
}

void Client::setServerKey(const QString & key)
{
	if (m->serverKey != key) {
		m->serverKey = key;
		emit serverKeyChanged();
	}
}

void Client::setUser(const QString & user)
{
	if (m->user != user) {
		m->user = user;
		emit userChanged();
	}
}

void Client::setAuthenticated(bool authenticated)
{
	if (m->authenticated != authenticated) {
		m->authenticated = authenticated;
		emit authenticatedChanged();
	}
}

void Client::startChannels(Session * session)
{
	m->channelsThread.start(session);
}

void Client::stopChannels()
{
	m->channelsThread.quit();
	m->channelsThread.wait();
}

void Client::handleChannelError(const QString & error)
{
	base::Prompt::Critical(error);
	logout();
}

Session * Client::lastSession()
{
	if (m->sessions.isEmpty())
		return nullptr;
	return m->sessions.last().value<Session *>();
}

Session * Client::takeLastSession()
{
	if (m->sessions.isEmpty())
		return nullptr;
	return m->sessions.takeLast().value<Session *>();
}

const Session * Client::lastSession() const
{
	if (m->sessions.isEmpty())
		return nullptr;
	return m->sessions.last().value<Session *>();
}

bool Client::verifyServer()
{
	CUTEHMI_UTILS_DEBUG("Verifying server...");

	m->settings.beginGroup(QSETTINGS_GROUP);
	QString storedServerKey = m->settings.value(serverKeySettingsKey()).toString();
	m->settings.endGroup();

	if (storedServerKey.isEmpty())
		emit serverKeyNew();
	else if (serverKey() != storedServerKey)
		emit serverKeyMismatch();
	else
		return true;

	return false;
}

QString Client::serverKeySettingsKey() const
{
	return QString("serverKey/") + serverHost() + "/" + QString::number(serverPort());
}

}
}

//(c)MPWZ: Copyright © 2017, Michal Policht, Wojciech Zygmuntowicz. All rights reserved.
//(c)MPWZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
