#ifndef CUTEHMI_STUPIDLIB_INCLUDE_STUPID_DS18B20HISTORY_HPP
#define CUTEHMI_STUPIDLIB_INCLUDE_STUPID_DS18B20HISTORY_HPP

#include "internal/common.hpp"
#include "internal/DS18B20HistoryWorker.hpp"

#include <charts/PointSeries.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace stupid {

class CUTEHMI_STUPID_API DS18B20History:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(cutehmi::charts::PointSeries * series READ series NOTIFY seriesChanged)
		Q_PROPERTY(qint64 from READ from WRITE setFrom NOTIFY fromChanged)
		Q_PROPERTY(qint64 to READ to WRITE setTo NOTIFY toChanged)
		Q_PROPERTY(qint64 minimum READ minimum NOTIFY minimumChanged)
		Q_PROPERTY(qint64 maximum READ maximum NOTIFY maximumChanged)
		Q_PROPERTY(bool updating READ updating NOTIFY updatingChanged)

		DS18B20History(std::unique_ptr<internal::DS18B20HistoryWorker> worker = nullptr, QObject * parent = 0);

		~DS18B20History() override;

		charts::PointSeries * series() const;

		qint64 from() const;

		void setFrom(qint64 from);

		qint64 to() const;

		void setTo(qint64 to);

		/**
		 * Minimum. Retrieves maximum timestamp value.
		 * @return timestamp value for which historcal data starts to be available.
		 *
		 * @threadsafe
		 */
		qint64 minimum() const;

		/**
		 * Maximum. Retrieves minimum timestamp value.
		 * @return timestamp value of most recent historcal data that is available.
		 *
		 * @threadsafe
		 */
		qint64 maximum() const;

		bool updating() const;

	public slots:
		/**
		 * Request update.
		 * @return @p true when request was accepted. If previous request has not finished yet, @p false is returned and request is rejected.
		 */
		bool requestUpdate();

	signals:
		void fromChanged();

		void toChanged();

		void seriesChanged();

		void minimumChanged();

		void maximumChanged();

		void updatingChanged();

	protected slots:
		void update();

	private:
		void setUpdating(bool updating);

		struct Members
		{
			std::unique_ptr<internal::DS18B20HistoryWorker> worker;
			charts::PointSeries * series;
			qint64 minimum;
			qint64 maximum;
			qint64 from;
			qint64 to;
			bool updating;
		};

		utils::MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
