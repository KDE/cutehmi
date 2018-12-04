#ifndef H_QML_CUTEHMI_CHARTS_SRC_CUTEHMI_CHARTS_QML_DATETIMEAXIS_HPP
#define H_QML_CUTEHMI_CHARTS_SRC_CUTEHMI_CHARTS_QML_DATETIMEAXIS_HPP

#include "TickedAxis.hpp"

namespace cutehmi {
namespace charts {
namespace qml {

class DateTimeAxis:
		public TickedAxis
{
	Q_OBJECT

	public:
		/**
		 * <principle id="cutehmi::charts::DateTimeAxis-ordered_interval_enum">
		 * Enum values are stored from smallest to largest intervals and are guaranteed to be contiguous.
		 * </principle>
		 */
		enum Interval {
			//<principle_ref id="cutehmi::charts::DateTimeAxis-ordered_interval_enum">
			MILLISECONDS,
			SECONDS,
			MINUTES,
			HOURS,
			DAYS,
			WEEKS,
			MONTHS,
			YEARS
			//</prinicple_ref>
		};
		Q_ENUM(Interval)

		Q_PROPERTY(Interval tickInterval READ tickInterval WRITE setTickInterval NOTIFY tickIntervalChanged)
		Q_PROPERTY(Interval minorTickInterval READ minorTickInterval WRITE setMinorTickInterval NOTIFY minorTickIntervalChanged)

		static constexpr Interval INITIAL_TICK_INTERVAL = DAYS;
		static constexpr Interval INITIAL_MINOR_TICK_INTERVAL = HOURS;

		DateTimeAxis(QQuickItem * parent = nullptr);

		Interval tickInterval() const;

		void setTickInterval(Interval interval);

		Interval minorTickInterval() const;

		void setMinorTickInterval(Interval interval);

		qreal mapToPlotArea(qreal value) const override;

	signals:
		void tickIntervalChanged();

		void minorTickIntervalChanged();

	protected:
		void walkTicks(std::function<void (qreal tick)> callback) const override;

		void walkMinorTicks(std::function<void (qreal tick)> callback) const override;

		void walkTickLabels(std::function<void (qreal labelPos)> callback) const override;

		QString tickToString(qreal tick) const override;

		QString boundToString(qreal tick) const override;

	private slots:
		void connectPlotArea(PlotArea * oldPlotArea);

		void recalcRatio();

		void connectOrientation();

	private:
		qreal tickMax() const;

		qreal approxTickIntervalToMSec(Interval interval) const;

		QDateTime roundTick(qreal tick, Interval tickInterval) const;

		void advanceTickDateTime(QDateTime & tickDT, Interval tickInterval) const;

		Interval m_tickInterval;
		Interval m_minorTickInterval;
		qreal m_screenScaleRatio;
};

}
}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
