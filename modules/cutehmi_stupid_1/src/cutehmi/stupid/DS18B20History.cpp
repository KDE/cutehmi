#include "../../../include/cutehmi/stupid/DS18B20History.hpp"

#include <QtDebug>

namespace cutehmi {
namespace stupid {

DS18B20History::DS18B20History(std::unique_ptr<internal::DS18B20HistoryWorker> worker, QObject * parent):
	QObject(parent),
	m(new Members{std::move(worker), new charts::PointSeries(this), 0, 0, 0, 0, false})
{
	if (m->worker) {
		m->worker->work();
		m->worker->wait();
		m->minimum = m->worker->results().minimum;
		m->maximum = m->worker->results().maximum;
		connect(m->worker.get(), & internal::DS18B20HistoryWorker::ready, this, & DS18B20History::update);
	}
}

DS18B20History::~DS18B20History()
{
	if (m->worker)
		m->worker->wait();
}

charts::PointSeries * DS18B20History::series() const
{
	return m->series;
}

qint64 DS18B20History::from() const
{
	return m->from;
}

void DS18B20History::setFrom(qint64 from)
{
	if (m->from != from) {
		m->from = from;
		emit fromChanged();
	}
}

qint64 DS18B20History::to() const
{
	return m->to;
}

void DS18B20History::setTo(qint64 to)
{
	if (m->to != to) {
		m->to = to;
		emit toChanged();
	}
}

qint64 DS18B20History::minimum() const
{
	return m->minimum;
}

qint64 DS18B20History::maximum() const
{
	return m->maximum;
}

bool DS18B20History::updating() const
{
	return m->updating;
}

bool DS18B20History::requestUpdate()
{
	if (m->worker) {
		if (m->worker->isWorking()) {
			CUTEHMI_LOG_DEBUG("Update request rejected - worker has not finished its previous job yet.");
			return false;
		} else {
			setUpdating(true);
			m->worker->setFrom(from());
			m->worker->setTo(to());
			m->worker->work();
			return true;
		}
	} else {
		CUTEHMI_LOG_DEBUG("Worker has not been set.");
		return false;
	}
}

void DS18B20History::update()
{
	const internal::DS18B20HistoryWorker::Results & results = m->worker->results();
	if (m->minimum != results.minimum) {
		m->minimum = results.minimum;
		emit minimumChanged();
	}
	if (m->maximum != results.maximum) {
		m->maximum = results.maximum;
		emit maximumChanged();
	}
	m->series->setData(results.data);
	setUpdating(false);
}

void DS18B20History::setUpdating(bool updating)
{
	if (m->updating != updating) {
		m->updating = updating;
		emit updatingChanged();
	}
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
