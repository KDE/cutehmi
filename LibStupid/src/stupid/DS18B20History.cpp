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
	m_to(0),
	m_updating(false)
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

bool DS18B20History::updating() const
{
	return m_updating;
}

bool DS18B20History::requestUpdate()
{
	if (m_worker != nullptr) {
		if (m_worker->isWorking()) {
			qDebug("Update request rejected - worker has not finished its previous job yet.");
			return false;
		} else {
			setUpdating(true);
			m_worker->setFrom(from());
			m_worker->setTo(to());
			m_worker->work();
			return true;
		}
	} else {
		qDebug("Worker has not been set.");
		return false;
	}
}

void DS18B20History::update()
{
	const DS18B20HistoryWorker::Results & results = m_worker->results();
	if (m_minimum != results.minimum) {
		m_minimum = results.minimum;
		emit minimumChanged();
	}
	if (m_maximum != results.maximum) {
		m_maximum = results.maximum;
		emit maximumChanged();
	}
	m_series->setData(results.data);
	setUpdating(false);
}

void DS18B20History::setUpdating(bool updating)
{
	if (m_updating != updating) {
		m_updating = updating;
		emit updatingChanged();
	}
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
