#include "../../../include/cutehmi/charts/PointSeries.hpp"

namespace cutehmi {
namespace charts {

PointSeries::PointSeries(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

PointSeries::~PointSeries()
{
}

int PointSeries::count() const
{
	return m->data.count();
}

void PointSeries::append(const QPointF & point)
{
	m->data.push_back(point);
}

const PointSeries::DataContainer & PointSeries::data() const
{
	return m->data;
}

void PointSeries::setData(const DataContainer & data)
{
	m->data = data;
	emit dataChanged();
}

void PointSeries::clear()
{
	m->data.clear();
}

const QPointF * PointSeries::rawData() const
{
	return m->data.data();
}

}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
