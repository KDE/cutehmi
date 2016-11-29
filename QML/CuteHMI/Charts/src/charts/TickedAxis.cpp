#include "TickedAxis.hpp"

#include <QPainter>

namespace cutehmi {
namespace charts {

constexpr qreal TickedAxis::INITIAL_TICK_LABEL_OFFSET;
//const QColor LabeledAxis::INITIAL_COLOR = Qt::gray;
//const QColor LabeledAxis::INITIAL_TEXT_COLOR = Qt::black;
//const QFont LabeledAxis::INITIAL_FONT = QFont();
//constexpr qreal LabeledAxis::INITIAL_THICKNESS;
//constexpr qreal LabeledAxis::INITIAL_AXIS_POSITION;
constexpr bool TickedAxis::INITIAL_BOUNDS;
constexpr bool TickedAxis::INITIAL_TICKS;
constexpr bool TickedAxis::INITIAL_MINOR_TICKS;

TickedAxis::TickedAxis(QQuickItem * parent):
	CartesianAxis(parent),
	m_tickLabelOffset(INITIAL_TICK_LABEL_OFFSET),
	m_tickLabelSpace(0.0),
//	m_color(INITIAL_COLOR),
//	m_textColor(INITIAL_TEXT_COLOR),
//	m_font(INITIAL_FONT),
//	m_thickness(INITIAL_THICKNESS),
//	m_axisPosition(INITIAL_AXIS_POSITION),
	m_bounds(INITIAL_BOUNDS),
	m_ticks(INITIAL_TICKS),
	m_minorTicks(INITIAL_MINOR_TICKS)
{
	// Connect signals that should trigger paint.
	connect(this, & TickedAxis::tickLabelOffsetChanged, this, & QQuickItem::update);
//	connect(this, & LabeledAxis::colorChanged, this, & QQuickItem::update);
//	connect(this, & LabeledAxis::textColorChanged, this, & QQuickItem::update);
//	connect(this, & LabeledAxis::fontChanged, this, & QQuickItem::update);
//	connect(this, & LabeledAxis::thicknessChanged, this, & QQuickItem::update);
//	connect(this, & LabeledAxis::axisPositionChanged, this, & QQuickItem::update);
	connect(this, & TickedAxis::boundsChanged, this, & QQuickItem::update);
	connect(this, & TickedAxis::ticksChanged, this, & QQuickItem::update);
	connect(this, & TickedAxis::minorTicksChanged, this, & QQuickItem::update);
}

qreal TickedAxis::tickLabelOffset() const
{
	return m_tickLabelOffset;
}

void TickedAxis::setTickLabelOffset(qreal offset)
{
	if (m_tickLabelOffset != offset) {
		m_tickLabelOffset = offset;
		emit tickLabelOffsetChanged();
	}
}

qreal TickedAxis::tickLabelSpace() const
{
	return m_tickLabelSpace;
}

//QColor LabeledAxis::color() const
//{
//	return m_color;
//}

//void LabeledAxis::setColor(const QColor & color)
//{
//	if (m_color != color) {
//		m_color = color;
//		emit colorChanged();
//	}
//}

//QColor LabeledAxis::textColor() const
//{
//	return m_textColor;
//}

//void LabeledAxis::setTextColor(const QColor & textColor)
//{
//	if (m_textColor != textColor) {
//		m_textColor = textColor;
//		emit textColorChanged();
//	}
//}

//QFont LabeledAxis::font() const
//{
//	return m_font;
//}

//void LabeledAxis::setFont(const QFont & font)
//{
//	if (m_font != font) {
//		m_font = font;
//		emit fontChanged();
//	}
//}

//qreal LabeledAxis::thickness() const
//{
//	return m_thickness;
//}

//void LabeledAxis::setThickness(qreal thickness)
//{
//	if (m_thickness != thickness) {
//		m_thickness = thickness;
//		emit thicknessChanged();
//	}
//}

//qreal LabeledAxis::axisPosition() const
//{
//	return m_axisPosition;
//}

//void LabeledAxis::setAxisPosition(qreal axisPosition)
//{
//	if (m_axisPosition != axisPosition) {
//		m_axisPosition = axisPosition;
//		emit axisPositionChanged();
//	}
//}

bool TickedAxis::bounds() const
{
	return m_bounds;
}

void TickedAxis::setBounds(bool bounds)
{
	if (m_bounds != bounds) {
		m_bounds = bounds;
		emit boundsChanged();
	}
}

bool TickedAxis::ticks() const
{
	return m_ticks;
}

void TickedAxis::setTicks(bool ticks)
{
	if (m_ticks != ticks) {
		m_ticks  = ticks;
		emit ticksChanged();
	}
}

bool TickedAxis::minorTicks() const
{
	return m_minorTicks;
}

void TickedAxis::setMinorTicks(bool minorTicks)
{
	if (m_minorTicks != minorTicks) {
		m_minorTicks  = minorTicks;
		emit minorTicksChanged();
	}
}

void TickedAxis::paint(QPainter * painter)
{
	if ((orientation() != Qt::Vertical) && (orientation() != Qt::Horizontal)) {
		painter->drawText(boundingRect(), Qt::AlignLeft | Qt::AlignTop, QString("TickedAxis::paint() - unsupported orientation: ") + QString::number(orientation()) + ".");
		return;
	}

	qreal labelSpace = 0.0;
	if (labelOffset() != 0.0) {
		QRectF labelSpaceRect = findLabelRect(painter);
		if (orientation() == Qt::Vertical)
			labelSpace = labelSpaceRect.width() + qAbs(labelOffset());
		else
			labelSpace = labelSpaceRect.height() + qAbs(labelOffset());
	}
	qreal tickLabelSpace = 0.0;
	if (tickLabelOffset() != 0.0) {
		QRectF tickLabelSpaceRect = findMaxTickLabelRect(painter);
		if (orientation() == Qt::Vertical)
			tickLabelSpace = tickLabelSpaceRect.width() + qAbs(tickLabelOffset());
		else
			tickLabelSpace = tickLabelSpaceRect.height() + qAbs(tickLabelOffset());
	}
	setTickLabelSpace(tickLabelSpace);
	setLabelSpace(qMax(labelSpace, tickLabelSpace));

	QRectF labelRect;
	if (labelOffset() != 0.0)
		labelRect = paintLabel(painter, labelPaintOffset());

	if (tickLabelOffset() != 0.0)
		paintTickLabels(painter, labelRect);

	if (minorTicks())
		paintMinorTicks(painter);
	if (ticks())
		paintTicks(painter);

	paintAxis(painter);
}

QString TickedAxis::boundToString(qreal bound) const
{
	return tickToString(bound);
}

void TickedAxis::setTickLabelSpace(qreal space)
{
	if (m_tickLabelSpace != space) {
		m_tickLabelSpace = space;
		emit tickLabelSpaceChanged();
	}
}

qreal TickedAxis::tickLabelPaintOffset() const
{
	if (plotArea()) {
		if (orientation() == Qt::Vertical) {
			if (axisPosition() <= plotArea()->horizontalCenter())
				return -tickLabelOffset();
		} else {
			if (axisPosition() < plotArea()->verticalCenter())
				return -tickLabelOffset();
		}
	}
	return tickLabelOffset();
}

void TickedAxis::paintTicks(QPainter * painter)
{
	painter->save();
	painter->setPen(QPen(color(), thickness()));

	// Draw bound ticks.
	if (bounds()) {
		if (orientation() == Qt::Vertical) {
			painter->drawLine(left(), mapToPlotArea(from()) + top(), right(), mapToPlotArea(from()) + top());
			painter->drawLine(left(), mapToPlotArea(to()) + top(), right(), mapToPlotArea(to()) + top());
		} else {
			painter->drawLine(mapToPlotArea(from()) + left(), top(), mapToPlotArea(from()) + left(), bottom());
			painter->drawLine(mapToPlotArea(to()) + left(), top(), mapToPlotArea(to()) + left(), bottom());
		}
	}

	// Draw rest of ticks.
	walkTicks([&](qreal tick) {
		qreal pos = mapToPlotArea(tick);	// Either x or y.
		if (orientation() == Qt::Vertical)
			painter->drawLine(left(), pos + top(), right(), pos + top());
		else
			painter->drawLine(pos + left(), top(), pos + left(), bottom());
	});

	painter->restore();
}

void TickedAxis::paintMinorTicks(QPainter * painter)
{
	painter->save();
	painter->setPen(QPen(color().lighter(), qMax(thickness() / 2.0, 1.0)));

	walkMinorTicks([&](qreal tick) {
		qreal pos = mapToPlotArea(tick);	// Either x or y.
		if (orientation() == Qt::Vertical)
			painter->drawLine(left(), pos + top(), right(), pos + top());
		else
			painter->drawLine(pos + left(), top(), pos + left(), bottom());
	});

	painter->restore();
}

void TickedAxis::paintTickLabels(QPainter * painter, const QRectF & labelRect)
{
	static constexpr int PRECEDING_RECT = 0;
	static constexpr int FOLLOWING_RECT = 1;
	// LABEL_RECT = 2 (constant unused).

	painter->save();
	painter->setPen(QPen(textColor(), thickness()));
	painter->setFont(font());

	// Draw bound labels.
	std::array<QRectF, 3> rects{QRectF(), QRectF(), labelRect};
	if (bounds()) {
		qreal pos = mapToPlotArea(from());
		pos += (orientation() == Qt::Vertical) ? top() : left();
		rects[PRECEDING_RECT] = paintTickLabel(painter, boundToString(from()), pos, 0.0, rects);
		pos = mapToPlotArea(to());
		pos += (orientation() == Qt::Vertical) ? top() : left();
		rects[FOLLOWING_RECT] = paintTickLabel(painter, boundToString(to()), pos, 1.0, rects);
	}

	// Draw tick labels.
	if (ticks())
		walkTickLabels([&](qreal tick) {
			qreal tickPos = (orientation() == Qt::Vertical) ? mapToPlotArea(tick) + top() : mapToPlotArea(tick) + left();
			QRectF newRect = paintTickLabel(painter, tickToString(tick), tickPos, 0.5, rects);
			if (newRect != QRectF())
				rects[PRECEDING_RECT] = newRect;
		});

	painter->restore();
}

QRectF TickedAxis::paintTickLabel(QPainter * painter, const QString & label, qreal pos, qreal displacement, const std::array<QRectF, 3> & rects)
{
	QRectF rect = painter->boundingRect(0, 0, 0, 0, Qt::AlignTop | Qt::AlignLeft, label);
	if (orientation() == Qt::Vertical) {
		if (tickLabelPaintOffset() < 0.0)
			rect.moveRight(axisPosition() + tickLabelPaintOffset());
		else
			rect.moveLeft(axisPosition() + tickLabelPaintOffset());
		rect.moveBottom(pos + rect.height() * displacement);
	} else {
		rect.moveLeft(pos - rect.width() * displacement);
		if (tickLabelPaintOffset() < 0.0)
			rect.moveBottom(axisPosition() + tickLabelPaintOffset());
		else
			rect.moveTop(axisPosition() + tickLabelPaintOffset());
	}
	qreal intersectAdjust = std::abs(tickLabelPaintOffset());
	QRectF rectAdjusted = rect.adjusted(-intersectAdjust, -intersectAdjust, intersectAdjust, intersectAdjust);
	if (rectAdjusted.intersects(rects[0]) || rectAdjusted.intersects(rects[1]) || rectAdjusted.intersects(rects[2]))
		return QRectF();
	else
		painter->drawText(rect, label);
	return rect;
}

QRectF TickedAxis::findMaxTickLabelRect(QPainter * painter) const
{
	QRectF curRect;
	QRectF maxRect;

	if (bounds()) {
		maxRect = painter->boundingRect(0, 0, 0, 0, Qt::AlignTop | Qt::AlignLeft, tickToString(from()));
		curRect = painter->boundingRect(0, 0, 0, 0, Qt::AlignTop | Qt::AlignLeft, tickToString(to()));
		maxRect.setWidth(qMax(maxRect.width(), curRect.width()));
		maxRect.setHeight(qMax(maxRect.height(), curRect.height()));
	}
	walkTickLabels([&](qreal tick) {
		curRect = painter->boundingRect(0, 0, 0, 0, Qt::AlignTop | Qt::AlignLeft, tickToString(tick));
		maxRect.setWidth(qMax(maxRect.width(), curRect.width()));
		maxRect.setHeight(qMax(maxRect.height(), curRect.height()));
	});
	return maxRect;
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
