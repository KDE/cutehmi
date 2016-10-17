#ifndef SCATTERPLOT_H
#define SCATTERPLOT_H

#include <QQuickPaintedItem>
#include <QColor>
#include <QVector>
#include <QPoint>
#include <QQmlListProperty>

#include <charts/PointSeries.hpp>

namespace cutehmi {
namespace charts {

class ScatterPlot:
		public QQuickPaintedItem
{
	Q_OBJECT

	Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
	Q_PROPERTY(qreal pointSize READ pointSize WRITE setPointSize NOTIFY pointSizeChanged)
	Q_PROPERTY(PointSeries * series READ series WRITE setSeries NOTIFY seriesChanged)
//	Q_PROPERTY(QQmlListProperty<QPoint> series READ series)

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

		void paint(QPainter * painter);

	signals:
		void colorChanged();

		void pointSizeChanged();

		void seriesChanged();

	private:
		typedef QVector<QPoint> SeriesDataContainer;

		static void Append(QQmlListProperty<QPoint> * property, QPoint * value);

		static int Count(QQmlListProperty<QPoint> * property);

		static QPoint * At(QQmlListProperty<QPoint> * property, int index);

		static void Clear(QQmlListProperty<QPoint> * property);

		QColor m_color;
		qreal m_pointSize;
//		SeriesDataContainer m_seriesData;
//		QQmlListProperty<QPoint> m_series;
		PointSeries * m_series;
};

}
}

#endif
