#include "DS18B20HistoryWorker.hpp"

#include <QSqlQuery>
#include <QVariant>
#include <QDateTime>
#include <QtDebug>

namespace cutehmi {
namespace stupid {

DS18B20HistoryWorker::DS18B20HistoryWorker(DatabaseThread & thread, const QString & w1Id):
	Worker(thread),
	m_connectionName(thread.dbData()->connectionName),
	m_w1Id(w1Id),
	m_results{0, 0, 0, 0, charts::PointSeries::DataContainer()}
{
}

void DS18B20HistoryWorker::setFrom(qint64 from)
{
	m_results.from = from;
}

void DS18B20HistoryWorker::setTo(qint64 to)
{
	m_results.to = to;
}

const DS18B20HistoryWorker::Results & DS18B20HistoryWorker::results() const
{
	return m_results;
}

void DS18B20HistoryWorker::job()
{
	QSqlQuery query(QSqlDatabase::database(m_connectionName, false));
	query.prepare("SELECT min(timestamp), max(timestamp) FROM ds18b20_history WHERE w1_device_id = (SELECT id FROM w1_device WHERE w1_id = :w1Id LIMIT 1)");
	query.bindValue(":w1Id", m_w1Id);
	query.exec();
	if (query.first()) {
		m_results.minimum = query.value(0).toDateTime().toMSecsSinceEpoch();
		m_results.maximum = query.value(1).toDateTime().toMSecsSinceEpoch();
	}

	m_results.data.clear();
	query.prepare("SELECT timestamp, temperature FROM ds18b20_history WHERE "
				  "w1_device_id = (SELECT id FROM w1_device WHERE w1_id = :w1Id LIMIT 1)"
				  "AND timestamp >= :from AND timestamp <= :to");
	query.bindValue(":w1Id", m_w1Id);
	query.bindValue(":from", QDateTime::fromMSecsSinceEpoch(m_results.from));
	query.bindValue(":to", QDateTime::fromMSecsSinceEpoch(m_results.to));
	query.exec();
	while (query.next())
		m_results.data.append(QPointF(query.value(0).toDateTime().toMSecsSinceEpoch(), static_cast<int32_t>(query.value(1).toLongLong())));
}

}
}
