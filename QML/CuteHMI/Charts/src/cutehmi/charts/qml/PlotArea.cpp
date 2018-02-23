#include "PlotArea.hpp"

namespace cutehmi {
namespace charts {
namespace qml {

PlotArea::PlotArea(QQuickItem * parent):
	QQuickItem(parent)
{
	connect(this, & QQuickItem::xChanged, this, & PlotArea::leftChanged);
	connect(this, & QQuickItem::xChanged, this, & PlotArea::rightChanged);
	connect(this, & QQuickItem::widthChanged, this, & PlotArea::rightChanged);
	connect(this, & QQuickItem::yChanged, this, & PlotArea::topChanged);
	connect(this, & QQuickItem::yChanged, this, & PlotArea::bottomChanged);
	connect(this, & QQuickItem::heightChanged, this, & PlotArea::bottomChanged);
	connect(this, & QQuickItem::xChanged, this, & PlotArea::horizontalCenterChanged);
	connect(this, & QQuickItem::widthChanged, this, & PlotArea::horizontalCenterChanged);
	connect(this, & QQuickItem::yChanged, this, & PlotArea::verticalCenterChanged);
	connect(this, & QQuickItem::heightChanged, this, & PlotArea::verticalCenterChanged);
}

qreal PlotArea::left() const
{
	return x();
}

qreal PlotArea::right() const
{
	return x() + width();
}

qreal PlotArea::top() const
{
	return y();
}

qreal PlotArea::bottom() const
{
	return y() + height();
}

qreal PlotArea::horizontalCenter() const
{
	return (x() + width()) / 2.0;
}

qreal PlotArea::verticalCenter() const
{
	return (y() + height()) / 2.0;
}

}
}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
