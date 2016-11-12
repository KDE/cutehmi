#ifndef CUTEHMI_LIBSTUPID_SRC_STUPID_DS18B20HISTORYWORKER_HPP
#define CUTEHMI_LIBSTUPID_SRC_STUPID_DS18B20HISTORYWORKER_HPP

#include "../platform.hpp"
#include "Worker.hpp"
#include "DatabaseThread.hpp"

#include <charts/PointSeries.hpp>

namespace cutehmi {
namespace stupid {

/**
 * DS18B20History update worker.
 */
class CUTEHMI_STUPID_API DS18B20HistoryWorker:
		public Worker
{
	public:
		struct Results
		{
			qint64 from;
			qint64 to;
			qint64 minimum;
			qint64 maximum;
			charts::PointSeries::DataContainer data;
		};

		DS18B20HistoryWorker(DatabaseThread & thread, const QString & w1Id);

		void setFrom(qint64 from);

		void setTo(qint64 to);

		const Results & results() const;

		void job() override;

	private:
		QString m_connectionName;
		QString m_w1Id;
		Results m_results;
};

}
}

#endif
