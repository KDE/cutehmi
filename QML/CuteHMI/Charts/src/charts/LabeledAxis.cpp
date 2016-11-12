#include "LabeledAxis.hpp"

#include <QPainter>

namespace cutehmi {
namespace charts {

constexpr qreal LabeledAxis::INITIAL_LABEL_OFFSET;
const QColor LabeledAxis::INITIAL_COLOR = Qt::gray;
const QColor LabeledAxis::INITIAL_TEXT_COLOR = Qt::black;
const QFont LabeledAxis::INITIAL_FONT = QFont();
constexpr qreal LabeledAxis::INITIAL_THICKNESS;
constexpr qreal LabeledAxis::INITIAL_AXIS_POSITION;
constexpr bool LabeledAxis::INITIAL_BOUNDS;
constexpr bool LabeledAxis::INITIAL_TICKS;
constexpr bool LabeledAxis::INITIAL_MINOR_TICKS;

LabeledAxis::LabeledAxis(QQuickItem * parent):
	CartesianAxis(parent),
	m_labelOffset(INITIAL_LABEL_OFFSET),
	m_labelSpace(0.0),
	m_color(INITIAL_COLOR),
	m_textColor(INITIAL_TEXT_COLOR),
	m_font(INITIAL_FONT),
	m_thickness(INITIAL_THICKNESS),
	m_axisPosition(INITIAL_AXIS_POSITION),
	m_bounds(INITIAL_BOUNDS),
	m_ticks(INITIAL_TICKS),
	m_minorTicks(INITIAL_MINOR_TICKS)
{
	// Connect signals that should trigger paint.
	connect(this, & LabeledAxis::labelOffsetChanged, this, & QQuickItem::update);
	connect(this, & LabeledAxis::colorChanged, this, & QQuickItem::update);
	connect(this, & LabeledAxis::textColorChanged, this, & QQuickItem::update);
	connect(this, & LabeledAxis::fontChanged, this, & QQuickItem::update);
	connect(this, & LabeledAxis::thicknessChanged, this, & QQuickItem::update);
	connect(this, & LabeledAxis::axisPositionChanged, this, & QQuickItem::update);
	connect(this, & LabeledAxis::boundsChanged, this, & QQuickItem::update);
	connect(this, & LabeledAxis::ticksChanged, this, & QQuickItem::update);
	connect(this, & LabeledAxis::minorTicksChanged, this, & QQuickItem::update);
}

qreal LabeledAxis::labelOffset() const
{
	return m_labelOffset;
}

void LabeledAxis::setLabelOffset(qreal offset)
{
	if (m_labelOffset != offset) {
		m_labelOffset = offset;
		emit labelOffsetChanged();
	}
}

qreal LabeledAxis::labelSpace() const
{
	return m_labelSpace;
}

QColor LabeledAxis::color() const
{
	return m_color;
}

void LabeledAxis::setColor(const QColor & color)
{
	if (m_color != color) {
		m_color = color;
		emit colorChanged();
	}
}

QColor LabeledAxis::textColor() const
{
	return m_textColor;
}

void LabeledAxis::setTextColor(const QColor & textColor)
{
	if (m_textColor != textColor) {
		m_textColor = textColor;
		emit textColorChanged();
	}
}

QFont LabeledAxis::font() const
{
	return m_font;
}

void LabeledAxis::setFont(const QFont & font)
{
	if (m_font != font) {
		m_font = font;
		emit fontChanged();
	}
}

qreal LabeledAxis::thickness() const
{
	return m_thickness;
}

void LabeledAxis::setThickness(qreal thickness)
{
	if (m_thickness != thickness) {
		m_thickness = thickness;
		emit thicknessChanged();
	}
}

qreal LabeledAxis::axisPosition() const
{
	return m_axisPosition;
}

void LabeledAxis::setAxisPosition(qreal axisPosition)
{
	if (m_axisPosition != axisPosition) {
		m_axisPosition = axisPosition;
		emit axisPositionChanged();
	}
}

bool LabeledAxis::bounds() const
{
	return m_bounds;
}

void LabeledAxis::setBounds(bool bounds)
{
	if (m_bounds != bounds) {
		m_bounds = bounds;
		emit boundsChanged();
	}
}

bool LabeledAxis::ticks() const
{
	return m_ticks;
}

void LabeledAxis::setTicks(bool ticks)
{
	if (m_ticks != ticks) {
		m_ticks  = ticks;
		emit ticksChanged();
	}
}

bool LabeledAxis::minorTicks() const
{
	return m_minorTicks;
}

void LabeledAxis::setMinorTicks(bool minorTicks)
{
	if (m_minorTicks != minorTicks) {
		m_minorTicks  = minorTicks;
		emit minorTicksChanged();
	}
}

void LabeledAxis::paint(QPainter * painter)
{
	QPen textPen(m_textColor, m_thickness);
	QPen mainPen(m_color, m_thickness);
	QPen minorPen(m_color.lighter(), qMax(m_thickness / 2.0, 1.0));

	painter->setPen(textPen);
	painter->setFont(m_font);

	// Paint text elements.
	if ((orientation() != Qt::Vertical) && (orientation() != Qt::Horizontal)) {
		painter->drawText(boundingRect(), Qt::AlignLeft | Qt::AlignTop, QString("LinearAxis unsupported orientation: ") + QString::number(orientation()) + ".");
		return;
	}
	QRectF labelSpaceRect = findMaxLabelRect(painter);
	if (orientation() == Qt::Vertical)
		setLabelSpace(labelSpaceRect.width() + qAbs(labelOffset()));
	else
		setLabelSpace(labelSpaceRect.height() + qAbs(labelOffset()));
	paintLabels(painter);

	// Paint main graphical elements.
	if (minorTicks()) {
		painter->setPen(minorPen);
		paintMinorTicks(painter);
	}
	if (ticks()) {
		painter->setPen(mainPen);
		paintTicks(painter);
	}
	// Draw axis.
	if (orientation() == Qt::Vertical)
		painter->drawLine(m_axisPosition, top(), m_axisPosition, bottom());
	else
		painter->drawLine(left(), m_axisPosition, right(), m_axisPosition);
}

QString LabeledAxis::boundToString(qreal bound) const
{
	return tickToString(bound);
}

void LabeledAxis::setLabelSpace(qreal space)
{
	if (m_labelSpace != space) {
		m_labelSpace = space;
		emit labelSpaceChanged();
	}
}

void LabeledAxis::paintTicks(QPainter * painter)
{
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
}

void LabeledAxis::paintMinorTicks(QPainter * painter)
{
	walkMinorTicks([&](qreal tick) {
		qreal pos = mapToPlotArea(tick);	// Either x or y.
		if (orientation() == Qt::Vertical)
			painter->drawLine(left(), pos + top(), right(), pos + top());
		else
			painter->drawLine(pos + left(), top(), pos + left(), bottom());
	});
}

void LabeledAxis::paintLabels(QPainter * painter)
{
	if (labelOffset() == 0.0)
		return;

	// Draw bound labels.
	QRectF precedingRect;
	QRectF followingRect;
	if (bounds()) {
		qreal pos = mapToPlotArea(from());
		pos += (orientation() == Qt::Vertical) ? top() : left();
		precedingRect = paintLabel(painter, boundToString(from()), pos, 0.0);
		pos = mapToPlotArea(to());
		pos += (orientation() == Qt::Vertical) ? top() : left();
		followingRect = paintLabel(painter, boundToString(to()), pos, 1.0, precedingRect);
	}

	// Draw tick labels.
	if (ticks())
		walkTickLabels([&](qreal tick) {
			qreal tickPos = (orientation() == Qt::Vertical) ? mapToPlotArea(tick) + top() : mapToPlotArea(tick) + left();
			QRectF newRect = paintLabel(painter, tickToString(tick), tickPos, 0.5, precedingRect, followingRect);
			if (newRect != QRectF())
				precedingRect = newRect;
		});
}

QRectF LabeledAxis::paintLabel(QPainter * painter, const QString & label, qreal pos, qreal displacement, const QRectF & r1, const QRectF & r2)
{
	QRectF rect = painter->boundingRect(0, 0, 0, 0, Qt::AlignTop | Qt::AlignLeft, label);
	if (orientation() == Qt::Vertical) {
		if (m_labelOffset < 0.0) {
			rect.moveRight(m_axisPosition + m_labelOffset);
			rect.moveBottom(pos + rect.height() * displacement);
		} else {
			rect.moveLeft(m_axisPosition + m_labelOffset);
			rect.moveBottom(pos + rect.height() * displacement);
		}
	} else {
		if (m_labelOffset < 0.0) {
			rect.moveLeft(pos - rect.width() * displacement);
			rect.moveBottom(m_axisPosition + m_labelOffset);
		} else {
			rect.moveLeft(pos - rect.width() * displacement);
			rect.moveTop(m_axisPosition + m_labelOffset);
		}
	}
	qreal intersectAdjust = std::abs(m_labelOffset);
	QRectF rectAdjusted = rect.adjusted(-intersectAdjust, -intersectAdjust, intersectAdjust, intersectAdjust);
	if (rectAdjusted.intersects(r1) || rectAdjusted.intersects(r2))
		return QRectF();
	else
		painter->drawText(rect, label);
	return rect;
}

QRectF LabeledAxis::findMaxLabelRect(QPainter * painter) const
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
