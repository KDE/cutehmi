#ifndef H_QML_CUTEHMI_CHARTS_SRC_CUTEHMI_CHARTS_QML_VALUEAXIS_HPP
#define H_QML_CUTEHMI_CHARTS_SRC_CUTEHMI_CHARTS_QML_VALUEAXIS_HPP

#include "PlotArea.hpp"

#include <QQuickPaintedItem>

namespace cutehmi {
namespace charts {
namespace qml {

/**
 * Value axis.
 *
 * @todo use QSG* and subclass QQuickItem if possible instead of QQuickPaintedItem.
 */
class ValueAxis:
		public QQuickPaintedItem
{
	Q_OBJECT

	public:
		static constexpr qreal INITIAL_FROM = 0.0;
		static constexpr qreal INITIAL_TO = 100.0;

		Q_PROPERTY(qreal from READ from WRITE setFrom NOTIFY fromChanged)
		Q_PROPERTY(qreal to READ to WRITE setTo NOTIFY toChanged)
		Q_PROPERTY(PlotArea * plotArea READ plotArea WRITE setPlotArea NOTIFY plotAreaChanged)

		ValueAxis(QQuickItem * parent = 0);

		qreal from() const;

		void setFrom(qreal from);

		qreal to() const;

		void setTo(qreal to);

		PlotArea * plotArea() const;

		void setPlotArea(PlotArea * plotArea);

		virtual qreal mapToPlotArea(qreal value) const = 0;

//		virtual bool contentContains(qreal point) const = 0;

	signals:
		void fromChanged();

		void toChanged();

		void plotAreaChanged(PlotArea * oldPlotArea);

	protected:
		qreal left() const;

		qreal right() const;

		qreal top() const;

		qreal bottom() const;

		qreal plotAreaWidth() const;

		qreal plotAreaHeight() const;

	private:
		qreal m_from;
		qreal m_to;
		PlotArea * m_plotArea;
};

}
}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
