#ifndef H_QML_CUTEHMI_CHARTS_SRC_CUTEHMI_CHARTS_QML_PLOTAREA_HPP
#define H_QML_CUTEHMI_CHARTS_SRC_CUTEHMI_CHARTS_QML_PLOTAREA_HPP

#include <QQuickItem>

namespace cutehmi {
namespace charts {
namespace qml {

class PlotArea:
		public QQuickItem
{
	Q_OBJECT

	public:
		Q_PROPERTY(qreal left READ left NOTIFY leftChanged STORED false)
		Q_PROPERTY(qreal right READ right NOTIFY rightChanged STORED false)
		Q_PROPERTY(qreal top READ top NOTIFY topChanged STORED false)
		Q_PROPERTY(qreal bottom READ bottom NOTIFY bottomChanged STORED false)
		Q_PROPERTY(qreal horizontalCenter READ horizontalCenter NOTIFY horizontalCenterChanged STORED false)
		Q_PROPERTY(qreal verticalCenter READ verticalCenter NOTIFY verticalCenterChanged STORED false)

		PlotArea(QQuickItem * parent = nullptr);

		qreal left() const;

		qreal right() const;

		qreal top() const;

		qreal bottom() const;

		qreal horizontalCenter() const;

		qreal verticalCenter() const;

	signals:
		void leftChanged();

		void rightChanged();

		void topChanged();

		void bottomChanged();

		void horizontalCenterChanged();

		void verticalCenterChanged();
};

}
}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
