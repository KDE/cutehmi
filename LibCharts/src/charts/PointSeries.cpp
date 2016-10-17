#include "PointSeries.hpp"

namespace cutehmi {
namespace charts {

PointSeries::PointSeries(QObject * parent):
	QObject(parent)
{
}

PointSeries::~PointSeries()
{
}

int PointSeries::count() const
{
	return m_data.count();
}

void PointSeries::append(const QPointF & point)
{
	m_data.push_back(point);
}

const PointSeries::DataContainer & PointSeries::data() const
{
	return m_data;
}

void PointSeries::setData(const DataContainer & data)
{
	m_data = data;
}

void PointSeries::clear()
{
	m_data.clear();
}

const QPointF * PointSeries::rawData() const
{
	return m_data.data();
}

}
}
