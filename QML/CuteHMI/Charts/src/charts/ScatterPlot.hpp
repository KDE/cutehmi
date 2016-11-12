#ifndef CUTEHMI_QML_CUTEHMI_CHARTS_SRC_CHARTS_SCATTERPLOT_HPP
#define CUTEHMI_QML_CUTEHMI_CHARTS_SRC_CHARTS_SCATTERPLOT_HPP

#include <QQuickPaintedItem>
#include <QColor>
#include <QVector>
#include <QPoint>
#include <QQmlListProperty>

#include <charts/PointSeries.hpp>

#include "ValueAxis.hpp"

namespace cutehmi {
namespace charts {

/**
 * Scatter plot.
 *
 * @todo use QSG* and subclass QQuickItem instead of QQuickPaintedItem.
 */
class ScatterPlot:
		public QQuickPaintedItem
{
	Q_OBJECT

	Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
	Q_PROPERTY(qreal pointSize READ pointSize WRITE setPointSize NOTIFY pointSizeChanged)
	Q_PROPERTY(PointSeries * series READ series WRITE setSeries NOTIFY seriesChanged)
	Q_PROPERTY(ValueAxis * xAxis READ xAxis WRITE setXAxis NOTIFY xAxisChanged)
	Q_PROPERTY(ValueAxis * yAxis READ yAxis WRITE setYAxis NOTIFY yAxisChanged)

	public:
		static const QColor INITIAL_COLOR;
		static constexpr qreal INITIAL_POINT_SIZE = 3.0;

		ScatterPlot(QQuickItem * parent = 0);

		QColor color() const;

		void setColor(const QColor & color);

		qreal pointSize() const;

		void setPointSize(qreal size);

//		QQmlListProperty<QPoint> series();

		PointSeries * series() const;

		void setSeries(PointSeries * series);

		ValueAxis * xAxis() const;

		void setXAxis(ValueAxis * axis);

		ValueAxis * yAxis() const;

		void setYAxis(ValueAxis * axis);

		void paint(QPainter * painter);

	signals:
		void colorChanged();

		void pointSizeChanged();

		void seriesChanged();

		void xAxisChanged();

		void yAxisChanged();

	private:
		typedef QVector<QPointF> PointsContainer;

		QColor m_color;
		qreal m_pointSize;
		PointSeries * m_series;
		ValueAxis * m_xAxis;
		ValueAxis * m_yAxis;
//		PointsContainer m_points;	// Points cache.
};

}
}

#endif
