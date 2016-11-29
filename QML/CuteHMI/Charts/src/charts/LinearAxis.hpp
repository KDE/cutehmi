#ifndef CUTEHMI_QML_CUTEHMI_CHARTS_SRC_CHARTS_LINEARAXIS_HPP
#define CUTEHMI_QML_CUTEHMI_CHARTS_SRC_CHARTS_LINEARAXIS_HPP

#include "TickedAxis.hpp"

#include <QColor>

#include <functional>

namespace cutehmi {
namespace charts {

/**
 * Linear axis.
 *
 * @note currently LinearAxis does not care about repainting, when size or position of @a plotArea is being modified.
 * So, if LinearAxis has not been moved along with PlotArea it may not be repainted.
 *
 * @todo use QSG*.
 */
class LinearAxis:
		public TickedAxis
{
	Q_OBJECT

	public:
		Q_PROPERTY(qreal tickInterval READ tickInterval WRITE setTickInterval NOTIFY tickIntervalChanged)
		Q_PROPERTY(qreal minorTickInterval READ minorTickInterval WRITE setMinorTickInterval NOTIFY minorTickIntervalChanged)
		Q_PROPERTY(int tickLabelPrecision READ tickLabelPrecision WRITE setTickLabelPrecision NOTIFY tickLabelPrecisionChanged)
		Q_PROPERTY(qreal axisScale READ axisScale WRITE setAxisScale NOTIFY axisScaleChanged)

		static constexpr qreal INITIAL_TICK_INTERVAL = 0.0;
		static constexpr qreal INITIAL_MINOR_TICK_INTERVAL = 0.0;
		static constexpr int INITIAL_TICK_LABEL_PRECISION = 6;
		static constexpr qreal INITIAL_AXIS_SCALE = 1.0;
		static constexpr char TICK_LABEL_FORMAT = 'g';

		LinearAxis(QQuickItem * parent = 0);

		qreal tickInterval() const;

		void setTickInterval(qreal interval);

		qreal minorTickInterval() const;

		void setMinorTickInterval(qreal interval);

		int tickLabelPrecision() const;

		void setTickLabelPrecision(int precision);

		qreal axisScale() const;

		void setAxisScale(qreal axisScale);

		qreal mapToPlotArea(qreal value) const override;

	signals:
		void tickIntervalChanged();

		void minorTickIntervalChanged();

		void tickLabelPrecisionChanged();

		void axisScaleChanged();

		void screenScaleRatioChanged();

	protected:
		void walkTicks(std::function<void (qreal tick)> callback) const override;

		void walkMinorTicks(std::function<void (qreal tick)> callback) const override;

		void walkTickLabels(std::function<void (qreal labelPos)> callback) const override;

		QString tickToString(qreal tick) const override;

	private slots:
		void connectPlotArea(PlotArea * oldPlotArea);

		void connectOrientation();

		void recalcRatio();

	private:
		qreal tickMax() const;

//		void paintTicks(QPainter * painter);

//		void paintMinorTicks(QPainter * painter);

//		void paintLabels(QPainter * painter);

////		QRectF paintLabel(QPainter * painter, const QString & label, qreal pos, qreal displacement, const QRectF & r1 = QRectF(), const QRectF & r2 = QRectF());

//		QRectF findMaxLabelRect(QPainter * painter) const;

//		Qt::Orientation m_orientation;
//		QColor m_color;
//		QColor m_textColor;
//		QFont m_font;
//		qreal m_thickness;
		qreal m_tickInterval;
		qreal m_minorTickInterval;
		int m_tickLabelPrecision;
//		qreal m_axisPosition;
		qreal m_axisScale;
//		bool m_bounds;
		qreal m_screenScaleRatio;
//		QStringList m_tickList;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
