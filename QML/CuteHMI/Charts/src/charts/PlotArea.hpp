#ifndef CUTEHMI_QML_CUTEHMI_CHARTS_SRC_CHARTS_PLOTAREA_HPP
#define CUTEHMI_QML_CUTEHMI_CHARTS_SRC_CHARTS_PLOTAREA_HPP

#include <QQuickItem>

namespace cutehmi {
namespace charts {

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

		PlotArea(QQuickItem * parent = 0);

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

#endif
