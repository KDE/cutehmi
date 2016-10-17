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
	m_series(nullptr)
//	m_series(this, & m_seriesData, ScatterPlot::Append, ScatterPlot::Count, ScatterPlot::At, ScatterPlot::Clear)
{
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
		m_series = series;
		emit seriesChanged();
	}
}

//QQmlListProperty<QPoint> ScatterPlot::series()
//{
//	return m_series;
//}

void ScatterPlot::paint(QPainter * painter)
{
//	painter->drawPie(boundingRect().adjusted(1, 1, -1, -1), 90 * 16, 290 * 16);
//	QPen pen;(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
	QPen pen(m_color, m_pointSize);
	painter->setPen(pen);

//	/ @todo - type safety!!!!!!!!!!!!!! QVector<QPoint> could be enforced by some header in LibCharts for example.
//	SeriesDataContainer * seriesData = static_cast<SeriesDataContainer *>(m_series.data);
//	painter->drawPoints(seriesData->constData(), seriesData->count());

	if (m_series != nullptr) {
//		painter->drawPoints(m_series->rawData(), m_series->count());
		for (PointSeries::DataContainer::const_iterator it = m_series->data().begin(); it != m_series->data().end(); ++it) {
//			qDebug() << "drawing point " << it->x() << " " << it->y();
			painter->drawPoint(*it);
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

void ScatterPlot::Append(QQmlListProperty<QPoint> * property, QPoint * value)
{
	SeriesDataContainer * seriesData = static_cast<SeriesDataContainer *>(property->data);
	seriesData->append(*value);
}

int ScatterPlot::Count(QQmlListProperty<QPoint> * property)
{
	SeriesDataContainer * seriesData = static_cast<SeriesDataContainer *>(property->data);
	return seriesData->count();
}

QPoint * ScatterPlot::At(QQmlListProperty<QPoint> * property, int index)
{
	SeriesDataContainer * seriesData = static_cast<SeriesDataContainer *>(property->data);
	return & (*seriesData)[index];
}

void ScatterPlot::Clear(QQmlListProperty<QPoint> * property)
{
	static_cast<SeriesDataContainer *>(property->data)->clear();
}

}
}
