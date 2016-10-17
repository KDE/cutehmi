#ifndef DS18B20HISTORY_H
#define DS18B20HISTORY_H

#include "../platform.hpp"

#include "DS18B20HistoryModel.hpp"
#include "Worker.hpp"

#include <charts/PointSeries.hpp>

#include <QObject>
#include <QMutex>
#include <QQmlListProperty>
#include <QPoint>

//class QSqlTableModel;

namespace cutehmi {
namespace stupid {

class DatabaseThread;

//<workaround id="LibStupid-1" target="Qt" cause="design">
//	"Nested Classes Cannot Have Signals or Slots".

/**
 * DS18B20History update worker.
 *
 * @todo move to Client, create there and pass constructed object to DS18B20History.
 */
class CUTEHMI_STUPID_API DS18B20History_UpdateWorker:
		public Worker
{
	public:
		struct Results
		{
			qint64 minimum;
			qint64 maximum;
//			DS18B20HistoryModel::DataContainer data;
			charts::PointSeries::DataContainer data;
		};

		DS18B20History_UpdateWorker(QThread & thread, QString connectionName);

		void job() override;

		const Results & results() const;

	private:
		QString m_connectionName;
		Results m_results;
};

//</workaround>

class CUTEHMI_STUPID_API DS18B20History:
		public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(DS18B20HistoryModel * model READ model NOTIFY modelChanged)	// @todo delete?
		Q_PROPERTY(cutehmi::charts::PointSeries * series READ series NOTIFY seriesChanged)
//		Q_PROPERTY(QQmlListProperty<QPoint> series READ series)
		Q_PROPERTY(qint64 from READ from WRITE setFrom NOTIFY fromChanged)
		Q_PROPERTY(qint64 to READ to WRITE setTo NOTIFY toChanged)

		DS18B20History(DatabaseThread * dbThread = nullptr, QObject * parent = 0);

		DS18B20HistoryModel * model();

//		const QQmlListProperty<QPoint> & series() const;

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
		Q_INVOKABLE qint64 minimum() const;

		/**
		 * Maximum. Retrieves minimum timestamp value.
		 * @return timestamp value of most recent historcal data that is available.
		 *
		 * @threadsafe
		 */
		Q_INVOKABLE qint64 maximum() const;

	public slots:
		void requestUpdate();

		void update();

	signals:
		void modelChanged();

		void fromChanged();

		void toChanged();

		void seriesChanged();

	private:
		class DataSeries
		{
			public:
				typedef QVector<QPoint> DataContainer;

				DataSeries(QObject * object);

				const QQmlListProperty<QPoint> & series() const;

				static int Count(QQmlListProperty<QPoint> * property);

				static QPoint * At(QQmlListProperty<QPoint> * property, int index);

			private:
				DataContainer m_data;
				QQmlListProperty<QPoint> m_series;
		};

		DatabaseThread * m_dbThread;
		DS18B20HistoryModel * m_model;
		DataSeries m_dataSeries;
		charts::PointSeries * m_series;
		qint64 m_minimum;
		qint64 m_maximum;
		qint64 m_from;
		qint64 m_to;
//		mutable QMutex m_dbUpdateMutex;	// Locks database updates.
		DS18B20History_UpdateWorker m_updateWorker;
};

}
}

#endif // DS18B20HISTORY_H
