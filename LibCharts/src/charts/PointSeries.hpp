#ifndef CUTEHMI_LIBCHARTS_SRC_CHARTS_POINTSERIES_HPP
#define CUTEHMI_LIBCHARTS_SRC_CHARTS_POINTSERIES_HPP

#include "../platform.hpp"

#include <QPoint>
#include <QVector>
#include <QObject>

namespace cutehmi {
namespace charts {

class CUTEHMI_CHARTS_API PointSeries:
		public QObject
{
	Q_OBJECT

	public:
		typedef QVector<QPointF> DataContainer;

		PointSeries(QObject * parent = nullptr);

		~PointSeries() override;

		int count() const;

		void append(const QPointF & point);

		const DataContainer & data() const;

		void setData(const DataContainer & data);

		void clear();

		//shift(const QPoint & point) // remove first and append point

		const QPointF * rawData() const;

	signals:
		void dataChanged();

	private:
		DataContainer m_data;
};

}
}

#endif
