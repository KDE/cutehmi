#include "Database.hpp"
#include "internal/DatabaseDictionary.hpp"

namespace cutehmi {
namespace shareddatabase {

const char * Database::INITIAL_TYPE = "QPSQL";
const char * Database::INITIAL_HOST = "localhost";
constexpr int Database::INITIAL_PORT;
const char * Database::INITIAL_NAME = "dbname";
const char * Database::INITIAL_USER = "user";
const char * Database::INITIAL_PASSWORD = "password";

bool Database::IsConnected(const QString & connectionName)
{
	if (internal::DatabaseDictionary::Instance().isManaged(connectionName))
		return internal::DatabaseDictionary::Instance().isConnected(connectionName);
	else {
		CUTEHMI_WARNING("Database connection '" << connectionName << "' is not managed by '" << CUTEHMI_SHAREDDATABASE_NAME << "' extension - assuming connection operates from main thread.");
		return QSqlDatabase::connectionNames().contains(connectionName);
	}
}

Database::Database(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

Database::~Database()
{
	closeConnection();
	m->thread.wait();
}

QString Database::type() const
{
	return m->config.data()->type;
}

void Database::setType(const QString & type)
{
	if (m->config.data()->type != type) {
		m->config.data()->type = type;
		emit typeChanged();
	}
}

QString Database::host() const
{
	return m->config.data()->host;
}

void Database::setHost(const QString & host)
{
	if (m->config.data()->host != host) {
		m->config.data()->host = host;
		emit hostChanged();
	}
}

int Database::port() const
{
	return m->config.data()->port;
}

void Database::setPort(int port)
{
	if (m->config.data()->port != port) {
		m->config.data()->port = port;
		emit portChanged();
	}
}

QString Database::name() const
{
	return m->config.data()->name;
}

void Database::setName(const QString & name)
{
	if (m->config.data()->name != name) {
		m->config.data()->name = name;
		emit nameChanged();
	}
}

QString Database::user() const
{
	return m->config.data()->user;
}

void Database::setUser(const QString & user)
{
	if (m->config.data()->user != user) {
		m->config.data()->user = user;
		emit userChanged();
	}
}

QString Database::password() const
{
	return m->config.data()->password;
}

void Database::setPassword(const QString & password)
{
	if (m->config.data()->password != password) {
		m->config.data()->password = password;
		emit passwordChanged();
	}
}

QString Database::connectionName() const
{
	return m->config.data()->connectionName;
}

void Database::setConnectionName(const QString & connectionName)
{
	if (m->config.data()->connectionName != connectionName) {
		if (!m->config.data()->connectionName.isNull())
			internal::DatabaseDictionary::Instance().removeManaged(m->config.data()->connectionName);
		m->config.data()->connectionName = connectionName;
		internal::DatabaseDictionary::Instance().addManaged(m->config.data()->connectionName);
		emit connectionNameChanged();
	}
}

bool Database::threaded() const
{
	return m->threaded;
}

void Database::setThreaded(bool threaded)
{
	if (m->threaded != threaded) {
		m->threaded = threaded;
		emit threadedChanged();
	}
}

void Database::configureStarted(QState * active, const QState * idling, const QState * yielding, AssignStatusFunction assignStatus)
{
	Q_UNUSED(idling)
	Q_UNUSED(yielding)

	assignStatus(*active, tr("Connected"));
}

void Database::configureStarting(QState * starting, AssignStatusFunction assignStatus)
{
	QState * connecting = new QState(starting);
	starting->setInitialState(connecting);
	assignStatus(*connecting, tr("Connecting"));
	connect(connecting, & QState::entered, this, & Database::initializeConnection);
}

void Database::configureStopping(QState * stopping, AssignStatusFunction assignStatus)
{
	QState * disconnecting = new QState(stopping);
	stopping->setInitialState(disconnecting);
	assignStatus(*disconnecting, tr("Disconnecting"));
	connect(disconnecting, & QState::entered, this, & Database::closeConnection);
}

void Database::configureBroken(QState * broken, AssignStatusFunction assignStatus)
{
	Q_UNUSED(assignStatus)

	connect(broken, & QState::entered, this, & Database::closeConnection);
}

void Database::configureRepairing(QState * repairing, AssignStatusFunction assignStatus)
{
	Q_UNUSED(assignStatus)

	connect(repairing, & QState::entered, this, & Database::initializeConnection);
}

void Database::configureEvacuating(QState * evacuating, AssignStatusFunction assignStatus)
{
	Q_UNUSED(assignStatus)

	connect(evacuating, & QState::entered, this, & Database::closeConnection);
}

std::unique_ptr<QAbstractTransition> Database::transitionToStarted() const
{
	return std::make_unique<QSignalTransition>(this, & Database::connected);
}

std::unique_ptr<QAbstractTransition> Database::transitionToStopped() const
{
	return std::make_unique<QSignalTransition>(this, & Database::disconnected);
}

std::unique_ptr<QAbstractTransition> Database::transitionToBroken() const
{
	return std::make_unique<QSignalTransition>(this, & Database::errored);
}

std::unique_ptr<QAbstractTransition> Database::transitionToYielding() const
{
	return nullptr;
}

std::unique_ptr<QAbstractTransition> Database::transitionToIdling() const
{
	return nullptr;
}

void Database::initializeConnection()
{
	m->connectionHandler.reset(new internal::DatabaseConnectionHandler(m->config));
	connect(m->connectionHandler.get(), & internal::DatabaseConnectionHandler::connected, this, & Database::onHandlerConnected);
	connect(m->connectionHandler.get(), & internal::DatabaseConnectionHandler::disconnected, this, & Database::onHandlerDisconnected);
	connect(m->connectionHandler.get(), & internal::DatabaseConnectionHandler::errored, this, & Database::errored);
	if (m->threaded) {
		internal::DatabaseDictionary::Instance().associateThread(m->config.data()->connectionName, & m->thread);
		m->thread.start(std::move(m->connectionHandler));
	} else {
		internal::DatabaseDictionary::Instance().associateThread(m->config.data()->connectionName, QThread::currentThread());
		m->connectionHandler->connect();
	}
}

void Database::closeConnection()
{
	if (m->thread.isRunning())
		m->thread.quit();
	else if (m->connectionHandler)
		m->connectionHandler->disconnect();
	else
		emit disconnected();
}

void Database::onHandlerConnected(QString connectionName)
{
	internal::DatabaseDictionary::Instance().addConnected(connectionName);
	emit connected();
}

void Database::onHandlerDisconnected(QString connectionName)
{
	emit disconnected();
	m->connectionHandler.reset();
	QSqlDatabase::removeDatabase(connectionName);
	internal::DatabaseDictionary::Instance().removeConnected(connectionName);
	internal::DatabaseDictionary::Instance().dissociateThread(connectionName);
}

}
}

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
