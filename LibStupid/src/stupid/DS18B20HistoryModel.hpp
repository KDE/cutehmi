#ifndef DS18B20HISTORYMODEL_H
#define DS18B20HISTORYMODEL_H

#include "../platform.hpp"

#include <QAbstractTableModel>
#include <QDateTime>

#include <cstdint>

namespace cutehmi {
namespace stupid {

class CUTEHMI_STUPID_API DS18B20HistoryModel:
		public QAbstractTableModel
{
	Q_OBJECT

	public:
		struct Data
		{
//			QDateTime timestamp;
			qint64 timestamp;
			int32_t temperature;
		};

		typedef QVector<Data> DataContainer;

		DS18B20HistoryModel(QObject * parent = nullptr);

		int rowCount(const QModelIndex & parent = QModelIndex()) const override;

		int columnCount(const QModelIndex & parent = QModelIndex()) const override;

		QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

		void setData(const DataContainer & data);

	private:
		DataContainer m_data;
};

}
}

#endif // DS18B20HISTORYMODEL_H
