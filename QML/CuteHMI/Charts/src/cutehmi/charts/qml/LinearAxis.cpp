#include "LinearAxis.hpp"

#include <QPainter>

#include <cmath>

namespace cutehmi {
namespace charts {
namespace qml {

constexpr qreal LinearAxis::INITIAL_TICK_INTERVAL;
constexpr qreal LinearAxis::INITIAL_MINOR_TICK_INTERVAL;
constexpr int LinearAxis::INITIAL_TICK_LABEL_PRECISION;
constexpr qreal LinearAxis::INITIAL_AXIS_SCALE;
constexpr char LinearAxis::TICK_LABEL_FORMAT;

LinearAxis::LinearAxis(QQuickItem * parent):
	TickedAxis(parent),
	m_tickInterval(INITIAL_TICK_INTERVAL),
	m_minorTickInterval(INITIAL_MINOR_TICK_INTERVAL),
	m_tickLabelPrecision(INITIAL_TICK_LABEL_PRECISION),
	m_axisScale(INITIAL_AXIS_SCALE)
{
	recalcRatio();
	switch (orientation()) {
		case Qt::Horizontal:
			connect(this, & LinearAxis::widthChanged, this, & LinearAxis::recalcRatio);
			break;
		case Qt::Vertical:
			connect(this, & LinearAxis::heightChanged, this, & LinearAxis::recalcRatio);
			break;
		default:
			qWarning("Unsupported orientation: %d.", orientation());
	}

	connect(this, & ValueAxis::fromChanged, this, & LinearAxis::recalcRatio);
	connect(this, & ValueAxis::toChanged, this, & LinearAxis::recalcRatio);
	connect(this, & ValueAxis::plotAreaChanged, this, & LinearAxis::connectPlotArea);
	connect(this, & CartesianAxis::orientationChanged, this, & LinearAxis::connectOrientation);

//	// Connect signals that should trigger paint.
//	connect(this, & LinearAxis::colorChanged, this, & QQuickItem::update);
//	connect(this, & LinearAxis::textColorChanged, this, & QQuickItem::update);
//	connect(this, & LinearAxis::fontChanged, this, & QQuickItem::update);
//	connect(this, & LinearAxis::thicknessChanged, this, & QQuickItem::update);
//	connect(this, & LinearAxis::fromChanged, this, & QQuickItem::update);
//	connect(this, & LinearAxis::toChanged, this, & QQuickItem::update);
	connect(this, & LinearAxis::tickIntervalChanged, this, & QQuickItem::update);
	connect(this, & LinearAxis::minorTickIntervalChanged, this, & QQuickItem::update);
	connect(this, & LinearAxis::tickLabelPrecisionChanged, this, & QQuickItem::update);
//	connect(this, & LinearAxis::axisPositionChanged, this, & QQuickItem::update);
	connect(this, & LinearAxis::axisScaleChanged, this, & QQuickItem::update);
	connect(this, & LinearAxis::screenScaleRatioChanged, this, & QQuickItem::update);
//	connect(this, & ValueAxis::plotAreaChanged, this, & QQuickItem::update);
}

qreal LinearAxis::tickInterval() const
{
	return m_tickInterval;
}

void LinearAxis::setTickInterval(qreal interval)
{
	if (m_tickInterval != interval) {
		m_tickInterval = interval;
		emit tickIntervalChanged();
	}
}

qreal LinearAxis::minorTickInterval() const
{
	return m_minorTickInterval;
}

void LinearAxis::setMinorTickInterval(qreal interval)
{
	if (m_minorTickInterval != interval) {
		m_minorTickInterval = interval;
		emit minorTickIntervalChanged();
	}

}

int LinearAxis::tickLabelPrecision() const
{
	return m_tickLabelPrecision;
}

void LinearAxis::setTickLabelPrecision(int precision)
{
	if (m_tickLabelPrecision != precision) {
		m_tickLabelPrecision = precision;
		emit tickLabelPrecisionChanged();
	}
}

qreal LinearAxis::axisScale() const
{
	return m_axisScale;
}

void LinearAxis::setAxisScale(qreal axisScale)
{
	if (m_axisScale != axisScale) {
		m_axisScale = axisScale;
		emit axisScaleChanged();
	}
}

qreal LinearAxis::mapToPlotArea(qreal value) const
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

void LinearAxis::walkTicks(std::function<void(qreal tick)> callback) const
{
	qreal tickInterval;
	if ((to() - from()) / m_tickInterval > tickMax())
		tickInterval = (to() - from()) / tickMax();
	else
		tickInterval = m_tickInterval;
	if ((tickInterval + from() != from()) && (tickInterval + to() != to()))
		for (qreal tick = from() + tickInterval - std::fmod(from(), tickInterval); tick < to(); tick += tickInterval)
			callback(tick);
}

void LinearAxis::walkMinorTicks(std::function<void(qreal tick)> callback) const
{
	qreal tickInterval;
	if ((to() - from()) / m_minorTickInterval > tickMax())
		tickInterval = (to() - from()) / tickMax();
	else
		tickInterval = m_minorTickInterval;
	if ((tickInterval + from() != from()) && (tickInterval + to() != to()))
		for (qreal tick = from() + tickInterval - std::fmod(from(), tickInterval); tick < to(); tick += tickInterval)
			callback(tick);
}

void LinearAxis::walkTickLabels(std::function<void(qreal labelPos)> callback) const
{
	qreal tickInterval;
	if ((to() - from()) / m_tickInterval > tickMax())
		tickInterval = (to() - from()) / tickMax();
	else
		tickInterval = m_tickInterval;
	if ((tickInterval + from() != from()) && (tickInterval + to() != to()))
		for (qreal pos = from() + tickInterval - std::fmod(from(), m_tickInterval); pos < to(); pos += tickInterval)
			callback(pos);
}

//bool LinearAxis::contentContains(qreal point) const
//{
//	// Note: comparing NaN to any other value will always return false.
//	switch (orientation()) {
//		case Qt::Horizontal:
//			return (point >= left()) && (point <= width() - right());
//		case Qt::Vertical:
//			return (point >= top()) && (point <= height() - bottom());
//	}
//	return false;
//}

QString LinearAxis::tickToString(qreal tick) const
{
	return QString::number(tick * m_axisScale, TICK_LABEL_FORMAT, m_tickLabelPrecision);
}

void LinearAxis::connectPlotArea(PlotArea * oldPlotArea)
{
	QQuickItem * oldEmitter = oldPlotArea ? static_cast<QQuickItem * >(oldPlotArea) : static_cast<QQuickItem * >(this);
	QQuickItem * newEmitter = plotArea() ? static_cast<QQuickItem * >(plotArea()) : static_cast<QQuickItem *>(this);
	switch (orientation()) {
		case Qt::Horizontal:
			disconnect(oldEmitter, & QQuickItem::widthChanged, this, & LinearAxis::recalcRatio);
			connect(newEmitter, & QQuickItem::widthChanged, this, & LinearAxis::recalcRatio);
			break;
		case Qt::Vertical:
			disconnect(oldEmitter, & QQuickItem::heightChanged, this, & LinearAxis::recalcRatio);
			connect(newEmitter, & QQuickItem::heightChanged, this, & LinearAxis::recalcRatio);
			break;
	}
	recalcRatio();
}

void LinearAxis::connectOrientation()
{
	QQuickItem * emitter = plotArea() ? static_cast<QQuickItem * >(plotArea()) : static_cast<QQuickItem *>(this);
	switch (orientation()) {
		case Qt::Horizontal:
			disconnect(emitter, & QQuickItem::heightChanged, this, & LinearAxis::recalcRatio);
			connect(emitter, & QQuickItem::widthChanged, this, & LinearAxis::recalcRatio);
			break;
		case Qt::Vertical:
			disconnect(emitter, & QQuickItem::widthChanged, this, & LinearAxis::recalcRatio);
			connect(emitter, & QQuickItem::heightChanged, this, & LinearAxis::recalcRatio);
			break;
		default:
			qWarning("Unsupported orientation: %d.", orientation());
	}
	recalcRatio();
}

void LinearAxis::recalcRatio()
{
	qreal oldRatio = m_screenScaleRatio;
	if (orientation() == Qt::Horizontal)
		m_screenScaleRatio = (plotAreaWidth()) / (to() - from());
	else
		m_screenScaleRatio = (plotAreaHeight()) / (to() - from());
	if (oldRatio != m_screenScaleRatio)
		emit screenScaleRatioChanged();
}

qreal LinearAxis::tickMax() const
{
	return (orientation() == Qt::Horizontal) ? width() : height();
}

//void LinearAxis::walkTicks(std::function<void(qreal tick)> callback, qreal tickInterval) const
//{
//	if ((tickInterval + from() != from()) && (tickInterval + to() != to()))
//		for (qreal tick = from() + tickInterval - std::fmod(from(), tickInterval); tick < to(); tick += tickInterval)
//			callback(tick);
//}

//void LinearAxis::updateTickList()
//{
//	m_tickList.clear();
//	walkTicks([](qreal tick) {
//		m_tickList.append(QString::number(tick, TICK_LABEL_FORMAT, m_tickLabelPrecision));
//	});
//}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
