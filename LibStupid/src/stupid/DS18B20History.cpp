#include "DS18B20History.hpp"

#include <QtDebug>

namespace cutehmi {
namespace stupid {

DS18B20History::DS18B20History(std::unique_ptr<DS18B20HistoryWorker> worker, QObject * parent):
	QObject(parent),
	m_worker(std::move(worker)),
	m_series(new charts::PointSeries(this)),
	m_minimum(0),
	m_maximum(0),
	m_from(0),
	m_to(0)
{
	if (m_worker != nullptr) {
		m_worker->work();
		m_worker->wait();
		m_minimum = m_worker->results().minimum;
		m_maximum = m_worker->results().maximum;
		connect(m_worker.get(), & DS18B20HistoryWorker::ready, this, & DS18B20History::update);
	}
}

DS18B20History::~DS18B20History()
{
	m_worker->wait();
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
	if (m_worker != nullptr) {
		if (m_worker->isWorking())
			qDebug("Update request rejected - worker has not finished its previous job yet.");
		else {
			m_worker->setFrom(from());
			m_worker->setTo(to());
			m_worker->work();
		}
	} else
		qDebug("Worker has not been set.");
}

void DS18B20History::update()
{
	qDebug("updating");
	const DS18B20HistoryWorker::Results & results = m_worker->results();
	if (m_minimum != results.minimum) {
		m_minimum = results.minimum;
		emit minimumChanged();
	}
	if (m_maximum != results.maximum) {
		m_maximum = results.maximum;
		emit maximumChanged();
	}
//	m_model->setData(results.data);
	qDebug("data size %d", results.data.count());
	m_series->setData(results.data);
}

}
}
