#include "DateTimeAxis.hpp"

#include <QPainter>
#include <QDateTime>

namespace cutehmi {
namespace charts {
namespace qml {

constexpr DateTimeAxis::interval_t DateTimeAxis::INITIAL_TICK_INTERVAL;
constexpr DateTimeAxis::interval_t DateTimeAxis::INITIAL_MINOR_TICK_INTERVAL;

DateTimeAxis::DateTimeAxis(QQuickItem * parent):
	TickedAxis(parent),
	m_tickInterval(INITIAL_TICK_INTERVAL),
	m_minorTickInterval(INITIAL_MINOR_TICK_INTERVAL)
{
	switch (orientation()) {
		case Qt::Horizontal:
			connect(this, & DateTimeAxis::widthChanged, this, & DateTimeAxis::recalcRatio);
			break;
		case Qt::Vertical:
			connect(this, & DateTimeAxis::heightChanged, this, & DateTimeAxis::recalcRatio);
			break;
		default:
			qWarning("Unsupported orientation: %d.", orientation());
	}
	connect(this, & DateTimeAxis::fromChanged, this, & DateTimeAxis::recalcRatio);
	connect(this, & DateTimeAxis::toChanged, this, & DateTimeAxis::recalcRatio);

	connect(this, & ValueAxis::plotAreaChanged, this, & DateTimeAxis::connectPlotArea);

	connect(this, & DateTimeAxis::orientationChanged, this, & DateTimeAxis::connectOrientation);

	// Connect signals that should trigger paint.
	connect(this, & DateTimeAxis::colorChanged, this, & QQuickItem::update);
	connect(this, & DateTimeAxis::textColorChanged, this, & QQuickItem::update);
	connect(this, & DateTimeAxis::fontChanged, this, & QQuickItem::update);
	connect(this, & DateTimeAxis::thicknessChanged, this, & QQuickItem::update);
	connect(this, & DateTimeAxis::fromChanged, this, & QQuickItem::update);
	connect(this, & DateTimeAxis::toChanged, this, & QQuickItem::update);
	connect(this, & DateTimeAxis::tickIntervalChanged, this, & QQuickItem::update);
	connect(this, & DateTimeAxis::minorTickIntervalChanged, this, & QQuickItem::update);
	connect(this, & DateTimeAxis::axisPositionChanged, this, & QQuickItem::update);
	connect(this, & ValueAxis::plotAreaChanged, this, & QQuickItem::update);
}

DateTimeAxis::interval_t DateTimeAxis::tickInterval() const
{
	return m_tickInterval;
}

void DateTimeAxis::setTickInterval(interval_t interval)
{
	if (m_tickInterval != interval) {
		m_tickInterval = interval;
		emit tickIntervalChanged();
	}
}

DateTimeAxis::interval_t DateTimeAxis::minorTickInterval() const
{
	return m_minorTickInterval;
}

void DateTimeAxis::setMinorTickInterval(interval_t interval)
{
	if (m_minorTickInterval != interval) {
		m_minorTickInterval = interval;
		emit minorTickIntervalChanged();
	}
}

qreal DateTimeAxis::mapToPlotArea(qreal value) const
{
	switch (orientation()) {
		case Qt::Horizontal:
			return (value - from()) * m_screenScaleRatio;
		case Qt::Vertical:
			return (to() - value) * m_screenScaleRatio;
		default:
			return qQNaN();
	}
}

void DateTimeAxis::walkTicks(std::function<void(qreal tick)> callback) const
{
	QDateTime curTickDT = roundTick(from(), m_tickInterval);
	QDateTime endDate = QDateTime::fromMSecsSinceEpoch(to());

	while (curTickDT < endDate) {
		callback(curTickDT.toMSecsSinceEpoch());
		advanceTickDateTime(curTickDT, m_tickInterval);
	}
}

void DateTimeAxis::walkMinorTicks(std::function<void(qreal tick)> callback) const
{
	QDateTime curTickDT = roundTick(from(), m_minorTickInterval);
	QDateTime endDate = QDateTime::fromMSecsSinceEpoch(to());

	while (curTickDT < endDate) {
		callback(curTickDT.toMSecsSinceEpoch());
		advanceTickDateTime(curTickDT, m_minorTickInterval);
	}
}

void DateTimeAxis::walkTickLabels(std::function<void(qreal labelPos)> callback) const
{
	QDateTime curTickDT = roundTick(from(), m_tickInterval);
	// Put labels in between ticks.
	if ((m_tickInterval == DAYS) ||
		(m_tickInterval == WEEKS) ||
		(m_tickInterval == MONTHS) ||
		(m_tickInterval == YEARS)) {
		QDateTime nextTickDT = curTickDT;
		advanceTickDateTime(nextTickDT, m_tickInterval);
		curTickDT = curTickDT.addMSecs((nextTickDT.toMSecsSinceEpoch() - curTickDT.toMSecsSinceEpoch()) / 2.0);
	}
	QDateTime endDate = QDateTime::fromMSecsSinceEpoch(to());

	while (curTickDT < endDate) {
		callback(curTickDT.toMSecsSinceEpoch());
		advanceTickDateTime(curTickDT, m_tickInterval);
	}
}

QString DateTimeAxis::tickToString(qreal tick) const
{
	QDateTime tickDT = QDateTime::fromMSecsSinceEpoch(tick);

	switch (m_tickInterval) {
		case MILLISECONDS:
			return tickDT.toString("zzz");
		case SECONDS:
			return tickDT.toString("ss");
		case MINUTES:
			return tickDT.toString("mm");
		case HOURS:
			return tickDT.toString("hh:mm");
		case DAYS:
			return tickDT.toString("ddd");
		case WEEKS:
			return QString::number(tickDT.date().weekNumber());
		case MONTHS:
			return tickDT.toString("MMM");
		case YEARS:
			return tickDT.toString("yyyy");
		default:
			qWarning("Unrecognized interval code '%d' (falling back to YEARS).", m_tickInterval);
			return tickDT.toString("yyyy");
	}
	return QDateTime::fromMSecsSinceEpoch(tick).toString();
}

QString DateTimeAxis::boundToString(qreal tick) const
{
	return QDateTime::fromMSecsSinceEpoch(tick).toString();
}

void DateTimeAxis::connectPlotArea(PlotArea * oldPlotArea)
{
	QQuickItem * oldEmitter = oldPlotArea ? static_cast<QQuickItem * >(oldPlotArea) : static_cast<QQuickItem * >(this);
	QQuickItem * newEmitter = plotArea() ? static_cast<QQuickItem * >(plotArea()) : static_cast<QQuickItem *>(this);
	switch (orientation()) {
		case Qt::Horizontal:
			disconnect(oldEmitter, & QQuickItem::widthChanged, this, & DateTimeAxis::recalcRatio);
			connect(newEmitter, & QQuickItem::widthChanged, this, & DateTimeAxis::recalcRatio);
			break;
		case Qt::Vertical:
			disconnect(oldEmitter, & QQuickItem::heightChanged, this, & DateTimeAxis::recalcRatio);
			connect(newEmitter, & QQuickItem::heightChanged, this, & DateTimeAxis::recalcRatio);
			break;
	}
	recalcRatio();
}

void DateTimeAxis::recalcRatio()
{
	switch (orientation()) {
		case Qt::Horizontal:
			m_screenScaleRatio = (plotAreaWidth()) / (to() - from());
			break;
		case Qt::Vertical:
			m_screenScaleRatio = (plotAreaHeight()) / (to() - from());
			break;
		default:
			m_screenScaleRatio = 0.0;
	}
}

void DateTimeAxis::connectOrientation()
{
	QQuickItem * emitter = plotArea() ? static_cast<QQuickItem * >(plotArea()) : static_cast<QQuickItem *>(this);
	switch (orientation()) {
		case Qt::Horizontal:
			disconnect(emitter, & QQuickItem::heightChanged, this, & DateTimeAxis::recalcRatio);
			connect(emitter, & QQuickItem::widthChanged, this, & DateTimeAxis::recalcRatio);
			break;
		case Qt::Vertical:
			disconnect(emitter, & QQuickItem::widthChanged, this, & DateTimeAxis::recalcRatio);
			connect(emitter, & QQuickItem::heightChanged, this, & DateTimeAxis::recalcRatio);
			break;
		default:
			qWarning("Unsupported orientation: %d.", orientation());
	}
	recalcRatio();
}

qreal DateTimeAxis::tickMax() const
{
	return (orientation() == Qt::Horizontal) ? width() : height();
}

qreal DateTimeAxis::approxTickIntervalToMSec(interval_t interval) const
{
	qreal result = 0.0;
	switch (interval) {
		case MILLISECONDS:
			return 1.0;
		case SECONDS:
			result = 1000.0;
		case MINUTES:
			result *= 60.0;
		case HOURS:
			result *= 60.0;
		case DAYS:
			result *= 24.0;
		case WEEKS:
			result *= 7.0;
		case MONTHS:
			result *= 30.0;
		case YEARS:
			result *= 365.0;
	}
	return result;
}

QDateTime DateTimeAxis::roundTick(qreal tick, interval_t tickInterval) const
{
	QDate d = QDateTime::fromMSecsSinceEpoch(tick).date();
	QTime t = QDateTime::fromMSecsSinceEpoch(tick).time();
	QDateTime roundTick;
	switch (tickInterval) {
		case MILLISECONDS:
			roundTick = QDateTime::fromMSecsSinceEpoch(from());
			break;
		case SECONDS:
			roundTick = QDateTime(QDate(d.year(), d.month(), d.day()), QTime(t.hour(), t.minute(), t.second()));
			roundTick = roundTick.addSecs(1);
			break;
		case MINUTES:
			roundTick = QDateTime(QDate(d.year(), d.month(), d.day()), QTime(t.hour(), t.minute()));
			roundTick = roundTick.addSecs(60);
			break;
		case HOURS:
			roundTick = QDateTime(QDate(d.year(), d.month(), d.day()), QTime(t.hour(), 0));
			roundTick = roundTick.addSecs(60 * 60);
			break;
		case DAYS:
			roundTick = QDateTime(QDate(d.year(), d.month(), d.day()));
			roundTick = roundTick.addDays(1);
			break;
		case WEEKS:
			roundTick = QDateTime(QDate(d.year(), d.month(), d.day() + 7 - d.dayOfWeek()));
			break;
		case MONTHS:
			roundTick = QDateTime(QDate(d.year(), d.month(), 0));
			roundTick = roundTick.addMonths(1);
			break;
		case YEARS:
			roundTick = QDateTime(QDate(d.year(), 0, 0));
			roundTick = roundTick.addYears(1);
			break;
	}
	return roundTick;
}

void DateTimeAxis::advanceTickDateTime(QDateTime & tickDT, interval_t tickInterval) const
{
	switch (tickInterval) {
		case MILLISECONDS:
			tickDT = tickDT.addMSecs(1);
			break;
		case SECONDS:
			tickDT = tickDT.addSecs(1);
			break;
		case MINUTES:
			tickDT = tickDT.addSecs(60);
			break;
		case HOURS:
			tickDT = tickDT.addSecs(60 * 60);
			break;
		case DAYS:
			tickDT = tickDT.addDays(1);
			break;
		case WEEKS:
			tickDT = tickDT.addDays(7);
			break;
		case MONTHS:
			tickDT = tickDT.addMonths(1);
			break;
		case YEARS:
			tickDT = tickDT.addYears(1);
			break;
	}
}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
