#include "ValueAxis.hpp"

namespace cutehmi {
namespace charts {
namespace qml {

constexpr qreal ValueAxis::INITIAL_FROM;
constexpr qreal ValueAxis::INITIAL_TO;

ValueAxis::ValueAxis(QQuickItem * parent):
	QQuickPaintedItem(parent),
	m_from(INITIAL_FROM),
	m_to(INITIAL_TO),
	m_plotArea(nullptr)
{
	connect(this, & ValueAxis::fromChanged, this, & QQuickItem::update);
	connect(this, & ValueAxis::toChanged, this, & QQuickItem::update);
	connect(this, & ValueAxis::plotAreaChanged, this, & QQuickItem::update);
}

qreal ValueAxis::from() const
{
	return m_from;
}

void ValueAxis::setFrom(qreal from)
{
	if (m_from != from) {
		m_from = from;
		emit fromChanged();
	}
}

qreal ValueAxis::to() const
{
	return m_to;
}

void ValueAxis::setTo(qreal to)
{
	if (m_to != to) {
		m_to = to;
		emit toChanged();
	}
}


PlotArea * ValueAxis::plotArea() const
{
	return m_plotArea;
}

void ValueAxis::setPlotArea(PlotArea * plotArea)
{
	if (m_plotArea != plotArea) {
		PlotArea * oldPlotArea = m_plotArea;
		m_plotArea = plotArea;
		emit plotAreaChanged(oldPlotArea);
	}
}

qreal ValueAxis::left() const
{
	return m_plotArea ? m_plotArea->left() : 0.0;
}

qreal ValueAxis::right() const
{
	return m_plotArea ? m_plotArea->right() : width();
}

qreal ValueAxis::top() const
{
	return m_plotArea ? m_plotArea->top() : 0.0;
}

qreal ValueAxis::bottom() const
{
	return m_plotArea ? m_plotArea->bottom() : height();
}

qreal ValueAxis::plotAreaWidth() const
{
	return m_plotArea ? m_plotArea->width() : width();
}

qreal ValueAxis::plotAreaHeight() const
{
	return m_plotArea ? m_plotArea->height() : height();
}


}
}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
