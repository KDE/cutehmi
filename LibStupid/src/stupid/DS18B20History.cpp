#include "DS18B20History.hpp"
#include "DatabaseThread.hpp"

#include <QMutexLocker>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QtDebug>

namespace cutehmi {
namespace stupid {

DS18B20History_UpdateWorker::DS18B20History_UpdateWorker(QThread & thread, QString connectionName):
	Worker(thread),
	m_connectionName(connectionName),
	m_results{0, 0, charts::PointSeries::DataContainer()}
{
}

void DS18B20History_UpdateWorker::job()
{
	qWarning("TODO create indexes on timestamp in STUPiD");	//temp

	QSqlQuery query(QSqlDatabase::database(m_connectionName, false));
	query.exec("SELECT min(timestamp), max(timestamp) FROM ds18b20_history WHERE w1_device_id = (SELECT id FROM w1_device WHERE w1_id = '28-000007ee1488' LIMIT 1)");
	if (query.first()) {
		m_results.minimum = query.value(0).toDateTime().toMSecsSinceEpoch();
		m_results.maximum = query.value(1).toDateTime().toMSecsSinceEpoch();
	}
//	qDebug() << m_results.minimum;
//	qDebug() << m_results.maximum;

	m_results.data.clear();
	query.exec("SELECT timestamp, temperature FROM ds18b20_history WHERE w1_device_id = (SELECT id FROM w1_device WHERE w1_id = '28-000007ee1488' LIMIT 1) LIMIT 5000");
	while (query.next())
		m_results.data.append(QPointF(query.value(0).toDateTime().toMSecsSinceEpoch(), static_cast<int32_t>(query.value(1).toLongLong())));
//		m_results.data.append(QPointF((query.value(0).toDateTime().toMSecsSinceEpoch() - m_results.minimum) / 1000000, static_cast<int32_t>(query.value(1).toLongLong()) / 100));
//		m_results.data.push_back(DS18B20HistoryModel::Data{query.value(0).toDateTime().toMSecsSinceEpoch(), static_cast<int32_t>(query.value(1).toLongLong())});

//QSqlDriver::QuerySize
//	QSqlDatabase::database(m_connectionName, false).driver()->hasFeature(QSqlDriver::QuerySize);

//	while (query.next()) {
//		QString w1Id = query.value(0).toString();
//		DS18B20::Data data;
//		data.plugged = query.value(1).toBool();
//		data.temperature = query.value(2).toLongLong();
//		data.crc = query.value(3).toInt();
//		data.crcOK = query.value(4).toBool();
//		data.timestamp = query.value(5).toDateTime();
//		if (m_ds18b20[w1Id].value<DS18B20 *>()->data().timestamp == data.timestamp)
//			data.expire = m_ds18b20[w1Id].value<DS18B20 *>()->data().expire;
//		else
//			data.expire.setMSecsSinceEpoch(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch() + m_daemonSleep * EXPIRE_DAEMON_CYCLES + EXPIRE_MIN_INTERVAL);
//		m_ds18b20[w1Id].value<DS18B20 *>()->updateData(data);
//	}
}

const DS18B20History_UpdateWorker::Results & DS18B20History_UpdateWorker::results() const
{
	return m_results;
}

DS18B20History::DS18B20History(DatabaseThread * dbThread, QObject * parent):
	QObject(parent),
	m_dbThread(dbThread),
	m_model(new DS18B20HistoryModel(this)),
	m_dataSeries(this),
	m_series(new charts::PointSeries(this)),
	m_minimum(0),
	m_maximum(0),
	m_from(0),
	m_to(0),
	m_updateWorker(*m_dbThread, dbThread->dbData()->connectionName)
{
	connect(& m_updateWorker, & DS18B20History_UpdateWorker::ready, this, & DS18B20History::update);
//	Worker dbWorker([this]() {
//		QSqlQuery query(QSqlDatabase::database(m_dbThread.dbData()->connectionName, false));
//		query.exec("SELECT w1_device.w1_id, w1_device.plugged, ds18b20.temperature, ds18b20.crc, ds18b20.crc_ok, ds18b20.timestamp "
//				   "FROM ds18b20 INNER JOIN w1_device ON ds18b20.w1_device_id = w1_device.id");
//		while (query.next()) {
//			QString w1Id = query.value(0).toString();
//			DS18B20::Data data;
//			data.plugged = query.value(1).toBool();
//			data.temperature = query.value(2).toLongLong();
//			data.crc = query.value(3).toInt();
//			data.crcOK = query.value(4).toBool();
//			data.timestamp = query.value(5).toDateTime();
//			if (m_ds18b20[w1Id].value<DS18B20 *>()->data().timestamp == data.timestamp)
//				data.expire = m_ds18b20[w1Id].value<DS18B20 *>()->data().expire;
//			else
//				data.expire.setMSecsSinceEpoch(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch() + m_daemonSleep * EXPIRE_DAEMON_CYCLES + EXPIRE_MIN_INTERVAL);
//			m_ds18b20[w1Id].value<DS18B20 *>()->updateData(data);
//		}
//	});
//	dbWorker.employ(m_dbThread);
//	dbWorker.wait();
//	m_series->append(QPoint(10, 10));	//temp
//	m_series->append(QPoint(50, 90));	//temp
}

DS18B20HistoryModel * DS18B20History::model()
{
	return m_model;
}

//const QQmlListProperty<QPoint> & DS18B20History::series() const
//{
//	return m_dataSeries.series();
//}

charts::PointSeries * DS18B20History::series() const
{
	return m_series;
}

qint64 DS18B20History::from() const
{
	return m_from;
}

void DS18B20History::setFrom(qint64 from)
{
	if (m_from != from) {
		m_from = from;
		emit fromChanged();
	}
}

qint64 DS18B20History::to() const
{
	return m_to;
}

void DS18B20History::setTo(qint64 to)
{
	if (m_to != to) {
		m_to = to;
		emit toChanged();
	}
}

qint64 DS18B20History::minimum() const
{
	return m_minimum;
}

qint64 DS18B20History::maximum() const
{
	return m_maximum;
}

void DS18B20History::requestUpdate()
{
	m_updateWorker.work();
}

void DS18B20History::update()
{
	qDebug("updating");
	const DS18B20History_UpdateWorker::Results & results = m_updateWorker.results();
	m_minimum = results.minimum;
	m_maximum = results.maximum;
//	m_model->setData(results.data);
	qDebug("data size %d", results.data.count());
	m_series->setData(results.data);
}

DS18B20History::DataSeries::DataSeries(QObject * object):
	m_series(object, & m_data, DS18B20History::DataSeries::Count, DS18B20History::DataSeries::At)
{
}

const QQmlListProperty<QPoint> & DS18B20History::DataSeries::series() const
{
	return m_series;
}

int DS18B20History::DataSeries::Count(QQmlListProperty<QPoint> * property)
{
	DataContainer * data = static_cast<DataContainer *>(property->data);
	return data->count();
}

QPoint * DS18B20History::DataSeries::At(QQmlListProperty<QPoint> * property, int index)
{
	DataContainer * data = static_cast<DataContainer *>(property->data);
	return & (*data)[index];
}


}
}
