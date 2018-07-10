#include "../../../../include/cutehmi/stupid/internal/DS18B20HistoryWorker.hpp"

#include <QSqlQuery>
#include <QVariant>
#include <QDateTime>
#include <QtDebug>

namespace cutehmi {
namespace stupid {
namespace internal {

DS18B20HistoryWorker::DS18B20HistoryWorker(DatabaseThread & thread, const QString & w1Id):
	Worker(thread),
	m(new Members{thread.dbData()->connectionName, w1Id, {0, 0, 0, 0, {}}})
{
}

void DS18B20HistoryWorker::setFrom(qint64 from)
{
	m->results.from = from;
}

void DS18B20HistoryWorker::setTo(qint64 to)
{
	m->results.to = to;
}

const DS18B20HistoryWorker::Results & DS18B20HistoryWorker::results() const
{
	return m->results;
}

void DS18B20HistoryWorker::job()
{
	QSqlQuery query(QSqlDatabase::database(m->connectionName, false));
	query.prepare("SELECT min(timestamp), max(timestamp) FROM ds18b20_history WHERE w1_device_id = (SELECT id FROM w1_device WHERE w1_id = :w1Id LIMIT 1)");
	query.bindValue(":w1Id", m->w1Id);
	query.exec();
	if (query.first()) {
		m->results.minimum = query.value(0).toDateTime().toMSecsSinceEpoch();
		m->results.maximum = query.value(1).toDateTime().toMSecsSinceEpoch();
	}

	m->results.data.clear();
	query.prepare("SELECT timestamp, temperature FROM ds18b20_history WHERE "
				  "w1_device_id = (SELECT id FROM w1_device WHERE w1_id = :w1Id LIMIT 1)"
				  "AND timestamp >= :from AND timestamp <= :to");
	query.bindValue(":w1Id", m->w1Id);
	query.bindValue(":from", QDateTime::fromMSecsSinceEpoch(m->results.from));
	query.bindValue(":to", QDateTime::fromMSecsSinceEpoch(m->results.to));
	query.exec();
	while (query.next())
		m->results.data.append(QPointF(query.value(0).toDateTime().toMSecsSinceEpoch(), static_cast<int32_t>(query.value(1).toLongLong())));
}

}
}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
