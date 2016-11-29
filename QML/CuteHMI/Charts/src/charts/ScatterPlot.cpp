#include "ScatterPlot.hpp"

#include <QPainter>

namespace cutehmi {
namespace charts {

const QColor ScatterPlot::INITIAL_COLOR = Qt::green;
constexpr qreal ScatterPlot::INITIAL_POINT_SIZE;

ScatterPlot::ScatterPlot(QQuickItem * parent):
	QQuickPaintedItem(parent),
	m_color(INITIAL_COLOR),
	m_pointSize(INITIAL_POINT_SIZE),
	m_series(nullptr),
	m_xAxis(nullptr),
	m_yAxis(nullptr)
{
	connect(this, & ScatterPlot::colorChanged, this, & QQuickItem::update);
	connect(this, & ScatterPlot::pointSizeChanged, this, & QQuickItem::update);
	connect(this, & ScatterPlot::seriesChanged, this, & QQuickItem::update);
	connect(this, & ScatterPlot::xAxisChanged, this, & QQuickItem::update);
	connect(this, & ScatterPlot::yAxisChanged, this, & QQuickItem::update);
}

QColor ScatterPlot::color() const
{
	return m_color;
}

void ScatterPlot::setColor(const QColor & color)
{
	if (m_color != color) {
		m_color = color;
		emit colorChanged();
	}
}

qreal ScatterPlot::pointSize() const
{
	return m_pointSize;
}

void ScatterPlot::setPointSize(qreal size)
{
	if (m_pointSize != size) {
		m_pointSize = size;
		emit pointSizeChanged();
	}
}

PointSeries * ScatterPlot::series() const
{
	return m_series;
}

void ScatterPlot::setSeries(PointSeries * series)
{
	if (m_series != series) {
		if (m_series != nullptr)
			m_series->disconnect(this);
		m_series = series;
		connect(m_series, & PointSeries::dataChanged, this, & QQuickItem::update);
//		connect(m_series, & PointSeries::dataChanged, this, & ScatterPlot::updatePoints);	//call update from updatePoints
		emit seriesChanged();
	}
}

ValueAxis * ScatterPlot::xAxis() const
{
	return m_xAxis;
}

void ScatterPlot::setXAxis(ValueAxis * axis)
{
	if (m_xAxis != axis) {
		m_xAxis = axis;
		emit xAxisChanged();
	}
}

ValueAxis * ScatterPlot::yAxis() const
{
	return m_yAxis;
}

void ScatterPlot::setYAxis(ValueAxis * axis)
{
	if (m_yAxis != axis) {
		m_yAxis = axis;
		emit yAxisChanged();
	}
}

//QQmlListProperty<QPoint> ScatterPlot::series()
//{
//	return m_series;
//}

void ScatterPlot::paint(QPainter * painter)
{
	QPen pen(m_color, m_pointSize);
	painter->setPen(pen);

	if (m_series != nullptr) {
//		painter->drawPoints(m_series->rawData(), m_series->count());
		for (PointSeries::DataContainer::const_iterator it = m_series->data().begin(); it != m_series->data().end(); ++it) {
//			qDebug() << "drawing point " << it->x() << " " << it->y();
			QPointF p(*it);
			if (m_xAxis != nullptr)
				p.setX(m_xAxis->mapToPlotArea(p.x()));
			if (m_yAxis != nullptr)
				p.setY(m_yAxis->mapToPlotArea(p.y()));
//			qDebug() << "point: " << p;
//			if (m_xAxis->contentContains(p.x()) && m_yAxis->contentContains(p.y()))
			if (qIsFinite(p.x()) && qIsFinite(p.y())) {
				if (p.y() < 0.0)
					painter->drawLine(p.x() - m_pointSize, m_pointSize / 2.0, p.x() + m_pointSize, m_pointSize / 2.0);
				else if (p.y() > height())
					painter->drawLine(p.x() - m_pointSize, height() - m_pointSize / 2.0, p.x() + m_pointSize, height() - m_pointSize / 2.0);
				else
					painter->drawPoint(p);
			}
		}
	}

	/*
	const int pointNum = 10000;
	QPoint * points = new QPoint[pointNum];
	for (int i = 0; i < pointNum; i++) {
		points[i].setX(qrand() % 1900);
		points[i].setY(qrand() % 1000);
	}
//	painter->drawPoint(100, 100);
	painter->drawPoints(points, pointNum);
	delete[] points;
	*/
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
