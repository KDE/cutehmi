#include "../../include/stupid/Client.hpp"
#include "../../include/stupid/internal/functions.hpp"

#include <QtConcurrent>
#include <QSqlQuery>
#include <QSqlDatabase>

namespace cutehmi {
namespace stupid {

Client::Client(QObject * parent):
	QObject(parent),
	m(new Members)
{
	// Forward database errors.
	QObject::connect(& m->dbThread, & internal::DatabaseThread::error, this, & Client::error);
}

Client::~Client()
{
	if (m->asyncConnector != nullptr)
		disconnect();
}

const QVariantMap & Client::ds18b20() const
{
	return m->ds18b20;
}

const QVariantMap & Client::ds18b20History() const
{
	return m->ds18b20History;
}

Client::DS18B20IdsContainer Client::ds18b20Ids() const
{
	return m->ds18b20.keys();
}

bool Client::isConnected() const
{
	return m->connected;
}

bool Client::isDisconnected() const
{
	return m->asyncConnector == nullptr;
}

void Client::moveDatabaseConnectionData(std::unique_ptr<stupid::DatabaseConnectionData> dbData)
{
	m->dbThread.moveDatabaseConnectionData(std::move(dbData));
}

void Client::checkDatabaseConnectionStatus()
{
	m->sqlErrors.push_back(QSqlDatabase::database(m->dbThread.dbData()->connectionName, false).lastError());
	processSQLErrors();
}

void Client::connect()
{
	if (!isDisconnected()) {
		CUTEHMI_UTILS_WARNING("Trying to connect, while not disconnected.");
		return;
	}

	m->asyncConnector = new internal::AsyncConnector(& m->dbThread, this);
	QObject::connect(m->asyncConnector, & internal::AsyncConnector::connected, this, & Client::asyncConnect);
	m->dbThread.start();	// asyncConnector will respond to m->dbThread->connected() signal.
}

void Client::disconnect()
{
	if (isDisconnected()) {
		CUTEHMI_UTILS_WARNING("Already disconnected.");
		return;
	} else if (!isConnected())
		CUTEHMI_UTILS_WARNING("Forcing disconnect, while connection has not been fully established (connection status is '" << static_cast<int>(m->asyncConnector->status()) << "'.");

	m->asyncConnector->disconnect(this);
	m->asyncConnector->deleteLater();

	if (m->dbThread.isRunning()) {
		m->dbThread.quit();
		m->dbThread.wait();
	}

	m->asyncConnector = nullptr;
	m->connected = false;
	emit disconnected();
	clearDevices();
}

void Client::readAll(const QAtomicInt & run)
{
	Q_UNUSED(run)

	if (!isConnected()) {
		CUTEHMI_UTILS_WARNING("Read attempt without established connection (connection status: '" << static_cast<int>(m->asyncConnector->status()) << "').");
		return;
	}

	internal::Worker dbWorker([this]() {
		QSqlQuery query(QSqlDatabase::database(m->dbThread.dbData()->connectionName, false));
		query.exec("SELECT w1_device.w1_id, w1_device.plugged, ds18b20.temperature, ds18b20.crc, ds18b20.crc_ok, ds18b20.timestamp "
				   "FROM ds18b20 INNER JOIN w1_device ON ds18b20.w1_device_id = w1_device.id");
		m->sqlErrors.push_back(query.lastError());
		while (query.next()) {
			QString w1Id = query.value(0).toString();
			DS18B20::Data data;
			data.plugged = query.value(1).toBool();
			data.temperature = query.value(2).toLongLong();
			data.crc = query.value(3).toInt();
			data.crcOK = query.value(4).toBool();
			data.timestamp = query.value(5).toDateTime();
			if (m->ds18b20[w1Id].value<DS18B20 *>()->data().timestamp == data.timestamp)
				data.expire = m->ds18b20[w1Id].value<DS18B20 *>()->data().expire;
			else
				data.expire.setMSecsSinceEpoch(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch() + m->daemonSleep * EXPIRE_DAEMON_CYCLES + EXPIRE_MIN_INTERVAL);
			m->ds18b20[w1Id].value<DS18B20 *>()->updateData(data);
		}
	});
	dbWorker.employ(m->dbThread);
	dbWorker.wait();
	processSQLErrors();
}

constexpr int Client::EXPIRE_DAEMON_CYCLES;
constexpr int Client::EXPIRE_MIN_INTERVAL;

void Client::asyncConnect(QObject * connector)
{
	if (m->asyncConnector != connector) {
		CUTEHMI_UTILS_WARNING("Received orphaned signal. Connection has been aborted.");
		return;
	}

	m->daemonSleep = m->asyncConnector->daemonSleep();
	for (QStringList::const_iterator w1Id = m->asyncConnector->w1Ids().begin(); w1Id != m->asyncConnector->w1Ids().end(); ++w1Id) {
		m->ds18b20.insert(*w1Id, QVariant::fromValue(new DS18B20));
		std::unique_ptr<internal::DS18B20HistoryWorker> worker(new internal::DS18B20HistoryWorker(m->dbThread, *w1Id));
		m->ds18b20History.insert(*w1Id, QVariant::fromValue(new DS18B20History(std::move(worker))));
	}
	CUTEHMI_UTILS_DEBUG("Connection has been established.");
	m->connected = true;
	emit connected();
}

void Client::processSQLErrors()
{
	for (SQLErrorsContainer::iterator it = m->sqlErrors.begin(); it != m->sqlErrors.end(); ++it)
		if (it->isValid())
			emit error(internal::errorInfo(*it));
	m->sqlErrors.clear();
}

void Client::clearDevices()
{
	for (QVariantMap::iterator it = m->ds18b20.begin(); it != m->ds18b20.end(); ++it)
		delete it.value().value<DS18B20 *>();
	m->ds18b20.clear();
	for (QVariantMap::iterator it = m->ds18b20History.begin(); it != m->ds18b20History.end(); ++it)
		delete it.value().value<DS18B20History *>();
	m->ds18b20History.clear();
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
