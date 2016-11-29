#include "Client.hpp"

#include <QtConcurrent>
#include <QSqlQuery>
#include <QSqlDatabase>

namespace cutehmi {
namespace stupid {

//QString Client::Error::str() const
//{
//	switch (code()) {
//		default:
//			return base::Error::str();
//	}
//}

Client::Client(QObject * parent):
	QObject(parent),
	m_daemonSleep(0)
{
	QObject::connect(& m_dbThread, & DatabaseThread::error, this, & Client::error);
	QObject::connect(& m_dbThread, & DatabaseThread::connected, this, & Client::connected);
	QObject::connect(& m_dbThread, & DatabaseThread::disconnected, this, & Client::disconnected);
}

Client::~Client()
{
	QThreadPool::globalInstance()->waitForDone();
}

const QVariantMap & Client::ds18b20() const
{
	return m_ds18b20;
}

const QVariantMap & Client::ds18b20History() const
{
	return m_ds18b20History;
}

Client::DS18B20IdsContainer Client::ds18b20Ids() const
{
	return m_ds18b20.keys();
}

void Client::moveDatabaseConnectionData(std::unique_ptr<stupid::DatabaseConnectionData> dbData)
{
	m_dbThread.moveDatabaseConnectionData(std::move(dbData));
}

void Client::init()
{
}

void Client::connect()
{
	m_dbThread.start();
	enumerateDevices();
	loadDaemonSleep();
}

void Client::disconnect()
{
	clearDevices();
	m_dbThread.quit();
	m_dbThread.wait();
}

void Client::readAll(const QAtomicInt & run)
{
	Q_UNUSED(run)

	Worker dbWorker([this]() {
		QSqlQuery query(QSqlDatabase::database(m_dbThread.dbData()->connectionName, false));
		query.exec("SELECT w1_device.w1_id, w1_device.plugged, ds18b20.temperature, ds18b20.crc, ds18b20.crc_ok, ds18b20.timestamp "
				   "FROM ds18b20 INNER JOIN w1_device ON ds18b20.w1_device_id = w1_device.id");
		while (query.next()) {
			QString w1Id = query.value(0).toString();
			DS18B20::Data data;
			data.plugged = query.value(1).toBool();
			data.temperature = query.value(2).toLongLong();
			data.crc = query.value(3).toInt();
			data.crcOK = query.value(4).toBool();
			data.timestamp = query.value(5).toDateTime();
			if (m_ds18b20[w1Id].value<DS18B20 *>()->data().timestamp == data.timestamp)
				data.expire = m_ds18b20[w1Id].value<DS18B20 *>()->data().expire;
			else
				data.expire.setMSecsSinceEpoch(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch() + m_daemonSleep * EXPIRE_DAEMON_CYCLES + EXPIRE_MIN_INTERVAL);
			m_ds18b20[w1Id].value<DS18B20 *>()->updateData(data);
		}
	});
	dbWorker.employ(m_dbThread);
	dbWorker.wait();
}

void Client::enumerateDevices()
{
	clearDevices();
	QStringList w1Ids;	// For proper thread affinity of DS18B20* objects do not create them inside m_dbThread, just store the results of a query.
	Worker dbWorker([this, & w1Ids]() {
		QSqlQuery query(QSqlDatabase::database(m_dbThread.dbData()->connectionName, false));
		query.exec("SELECT w1_device.w1_id "
				   "FROM ds18b20 INNER JOIN w1_device ON ds18b20.w1_device_id = w1_device.id");
		while (query.next())
			w1Ids.append(query.value(0).toString());
	});
	dbWorker.employ(m_dbThread);
	dbWorker.wait();
	for (QStringList::const_iterator w1Id = w1Ids.begin(); w1Id != w1Ids.end(); ++w1Id) {
		m_ds18b20.insert(*w1Id, QVariant::fromValue(new DS18B20));
		std::unique_ptr<DS18B20HistoryWorker> worker(new DS18B20HistoryWorker(m_dbThread, *w1Id));
		m_ds18b20History.insert(*w1Id, QVariant::fromValue(new DS18B20History(std::move(worker))));
	}
}

void Client::loadDaemonSleep()
{
	Worker dbWorker([this]() {
		QSqlQuery query(QSqlDatabase::database(m_dbThread.dbData()->connectionName, false));
		query.exec("SELECT daemon_sleep FROM settings");
		while (query.next())
			m_daemonSleep = query.value(0).toLongLong();
	});
	dbWorker.employ(m_dbThread);
	dbWorker.wait();
}

void Client::clearDevices()
{
	for (QVariantMap::iterator it = m_ds18b20.begin(); it != m_ds18b20.end(); ++it)
		delete it.value().value<DS18B20 *>();
	m_ds18b20.clear();
	for (QVariantMap::iterator it = m_ds18b20History.begin(); it != m_ds18b20History.end(); ++it)
		delete it.value().value<DS18B20History *>();
	m_ds18b20History.clear();
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
