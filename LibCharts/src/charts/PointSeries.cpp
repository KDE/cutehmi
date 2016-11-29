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
	emit dataChanged();
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

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
