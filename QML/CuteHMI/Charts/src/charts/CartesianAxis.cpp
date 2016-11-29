#include "CartesianAxis.hpp"

#include <QPainter>

namespace cutehmi {
namespace charts {

constexpr Qt::Orientation CartesianAxis::INITIAL_ORIENTATION;
const QString CartesianAxis::INITIAL_LABEL = QString("Axis Label");
constexpr qreal CartesianAxis::INITIAL_LABEL_OFFSET;
constexpr qreal CartesianAxis::INITIAL_LABEL_PLACEMENT;
constexpr bool CartesianAxis::INITIAL_ORIENT_LABEL;
const QColor CartesianAxis::INITIAL_COLOR = Qt::gray;
const QColor CartesianAxis::INITIAL_TEXT_COLOR = Qt::black;
const QFont CartesianAxis::INITIAL_FONT = QFont();
constexpr qreal CartesianAxis::INITIAL_THICKNESS;
constexpr qreal CartesianAxis::INITIAL_AXIS_POSITION;

CartesianAxis::CartesianAxis(QQuickItem * parent):
	ValueAxis(parent),
	m_orientation(INITIAL_ORIENTATION),
	m_label(INITIAL_LABEL),
	m_labelOffset(INITIAL_LABEL_OFFSET),
	m_labelPlacement(INITIAL_LABEL_PLACEMENT),
	m_orientLabel(INITIAL_ORIENT_LABEL),
	m_labelSpace(0.0),
	m_color(INITIAL_COLOR),
	m_textColor(INITIAL_TEXT_COLOR),
	m_font(INITIAL_FONT),
	m_thickness(INITIAL_THICKNESS),
	m_axisPosition(INITIAL_AXIS_POSITION)
{
	connect(this, & CartesianAxis::orientationChanged, this, & QQuickItem::update);
	connect(this, & CartesianAxis::labelChanged, this, & QQuickItem::update);
	connect(this, & CartesianAxis::labelOffsetChanged, this, & QQuickItem::update);
	connect(this, & CartesianAxis::labelPlacementChanged, this, & QQuickItem::update);
	connect(this, & CartesianAxis::orientLabelChanged, this, & QQuickItem::update);
	connect(this, & CartesianAxis::colorChanged, this, & QQuickItem::update);
	connect(this, & CartesianAxis::textColorChanged, this, & QQuickItem::update);
	connect(this, & CartesianAxis::fontChanged, this, & QQuickItem::update);
	connect(this, & CartesianAxis::thicknessChanged, this, & QQuickItem::update);
	connect(this, & CartesianAxis::axisPositionChanged, this, & QQuickItem::update);
}

Qt::Orientation CartesianAxis::orientation() const
{
	return m_orientation;
}

void CartesianAxis::setOrientation(Qt::Orientation orientation)
{
	if (m_orientation != orientation) {
		m_orientation = orientation;
		emit orientationChanged();
	}
}

QString CartesianAxis::label() const
{
	return m_label;
}

void CartesianAxis::setLabel(const QString & label)
{
	if (m_label != label) {
		m_label = label;
		emit labelChanged();
	}
}

qreal CartesianAxis::labelOffset() const
{
	return m_labelOffset;
}

void CartesianAxis::setLabelOffset(qreal offset)
{
	if (m_labelOffset != offset) {
		m_labelOffset = offset;
		emit labelOffsetChanged();
	}
}

qreal CartesianAxis::labelPlacement() const
{
	return m_labelPlacement;
}

void CartesianAxis::setLabelPlacement(qreal placement)
{
	if (m_labelPlacement != placement) {
		m_labelPlacement = placement;
		emit labelPlacementChanged();
	}
}

bool CartesianAxis::orientLabel() const
{
	return m_orientLabel;
}

void CartesianAxis::setOrientLabel(bool orientLabel)
{
	if (m_orientLabel != orientLabel) {
		m_orientLabel = orientLabel;
		emit orientLabelChanged();
	}
}

qreal CartesianAxis::labelSpace() const
{
	return m_labelSpace;
}

QColor CartesianAxis::color() const
{
	return m_color;
}

void CartesianAxis::setColor(const QColor & color)
{
	if (m_color != color) {
		m_color = color;
		emit colorChanged();
	}
}

QColor CartesianAxis::textColor() const
{
	return m_textColor;
}

void CartesianAxis::setTextColor(const QColor & textColor)
{
	if (m_textColor != textColor) {
		m_textColor = textColor;
		emit textColorChanged();
	}
}

QFont CartesianAxis::font() const
{
	return m_font;
}

void CartesianAxis::setFont(const QFont & font)
{
	if (m_font != font) {
		m_font = font;
		emit fontChanged();
	}
}

qreal CartesianAxis::thickness() const
{
	return m_thickness;
}

void CartesianAxis::setThickness(qreal thickness)
{
	if (m_thickness != thickness) {
		m_thickness = thickness;
		emit thicknessChanged();
	}
}

qreal CartesianAxis::axisPosition() const
{
	return m_axisPosition;
}

void CartesianAxis::setAxisPosition(qreal axisPosition)
{
	if (m_axisPosition != axisPosition) {
		m_axisPosition = axisPosition;
		emit axisPositionChanged();
	}
}

void CartesianAxis::paint(QPainter * painter)
{
	if ((orientation() != Qt::Vertical) && (orientation() != Qt::Horizontal)) {
		painter->drawText(boundingRect(), Qt::AlignLeft | Qt::AlignTop, QString("CartesianAxis::paint() - unsupported orientation: ") + QString::number(orientation()) + ".");
		return;
	}

	if (labelOffset() != 0.0) {
		QRectF labelSpaceRect = findLabelRect(painter);
		if (orientation() == Qt::Vertical)
			setLabelSpace(labelSpaceRect.width() + qAbs(labelOffset()));
		else
			setLabelSpace(labelSpaceRect.height() + qAbs(labelOffset()));
		paintLabel(painter, labelPaintOffset());
	} else
		setLabelSpace(0.0);

	paintAxis(painter);
}

void CartesianAxis::setLabelSpace(qreal space)
{
	if (m_labelSpace != space) {
		m_labelSpace = space;
		emit labelSpaceChanged();
	}
}

void CartesianAxis::paintAxis(QPainter * painter)
{
	painter->save();
	painter->setPen(QPen(color(), thickness()));

	if (orientation() == Qt::Vertical)
		painter->drawLine(axisPosition(), top(), axisPosition(), bottom());
	else
		painter->drawLine(left(), axisPosition(), right(), axisPosition());

	painter->restore();
}

QRectF CartesianAxis::paintLabel(QPainter * painter, qreal offset)
{
	painter->save();
	painter->setPen(QPen(textColor(), thickness()));
	painter->setFont(font());

	QRectF rect = painter->boundingRect(0, 0, 0, 0, Qt::AlignTop | Qt::AlignLeft, label());
	if (orientation() == Qt::Vertical) {
		if (orientLabel()) {
			// rect must remain untransformed while painting, hence width is swapped with height.
			qreal dy = bottom() - labelPlacement() * (plotAreaHeight() - rect.width());
			qreal dx;
			if (offset < 0.0)
				dx = axisPosition() - rect.height() + offset;
			else
				dx = axisPosition() + offset;
			painter->translate(dx, dy);
			painter->rotate(-90);
			painter->drawText(rect, label());

			// Apply same transformations to the resulting rect.
			rect.translate(dx, dy - rect.width());
			rect = rect.transposed();
		} else {
			if (offset < 0.0)
				rect.moveRight(axisPosition() + offset);
			else
				rect.moveLeft(axisPosition() + offset);
			rect.moveBottom(bottom() - labelPlacement() * (plotAreaHeight() - rect.height()));
			painter->drawText(rect, label());
		}
	} else {
		rect.moveLeft(left() + labelPlacement() * (plotAreaWidth() - rect.width()));
		if (offset < 0.0)
			rect.moveBottom(axisPosition() + offset);
		else
			rect.moveTop(axisPosition() + offset);
		painter->drawText(rect, label());
	}

	painter->restore();

	return rect;
}

QRectF CartesianAxis::findLabelRect(QPainter * painter) const
{
	QRectF rect = painter->boundingRect(0, 0, 0, 0, Qt::AlignTop | Qt::AlignLeft, label());
	if ((orientation() == Qt::Vertical) && orientLabel())
		return rect.transposed();
	return rect;
}

qreal CartesianAxis::labelPaintOffset() const
{
	if (plotArea()) {
		if (orientation() == Qt::Vertical) {
			if (axisPosition() <= plotArea()->horizontalCenter())
				return -labelOffset();
		} else {
			if (axisPosition() < plotArea()->verticalCenter())
				return -labelOffset();
		}
	}
	return labelOffset();
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
