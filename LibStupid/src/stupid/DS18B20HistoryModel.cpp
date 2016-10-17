#include "DS18B20HistoryModel.hpp"

namespace cutehmi {
namespace stupid {

DS18B20HistoryModel::DS18B20HistoryModel(QObject * parent):
	QAbstractTableModel(parent)
{
//	m_data.push_back(Data{QDateTime::fromMSecsSinceEpoch(10), 2456});
//	m_data.push_back(Data{QDateTime::fromMSecsSinceEpoch(20), 1456});
//	m_data.push_back(Data{QDateTime::fromMSecsSinceEpoch(30), 4456});
//	m_data.push_back(Data{2000000000, 2456});
//	m_data.push_back(Data{14000000000, 1456});
//	m_data.push_back(Data{0x4000000000000000, 4456});
//	m_data.push_back(Data{QDateTime::fromMSecsSinceEpoch(20), 1456});
//	m_data.push_back(Data{QDateTime::fromMSecsSinceEpoch(30), 4456});
//	m_data.push_back(Data{10, 2456});
//	m_data.push_back(Data{20, 1456});
//	m_data.push_back(Data{30, 4456});
}

int DS18B20HistoryModel::rowCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent)

	return m_data.count();
}

int DS18B20HistoryModel::columnCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent);

	return 2;
}

QVariant DS18B20HistoryModel::data(const QModelIndex & index, int role) const
{
	int row = index.row();
	int column = index.column();

	if (row >= m_data.count() || row < 0)
		return QVariant();

	if (column >= 2 || column < 0)
		return QVariant();

	if (role == Qt::DisplayRole) {
		if (column == 0)
			return m_data.at(row).timestamp;
		else if (column == 1)
			return m_data.at(row).temperature;
	}

	return QVariant();
}

void DS18B20HistoryModel::setData(const DataContainer & data)
{
	qDebug("data size before set %d", m_data.size());

////	m_data[1].temperature += 100;
//	emit beginInsertRows(QModelIndex(), m_data.count(), m_data.count());
//	m_data.push_back(Data{m_data[m_data.count() - 1].timestamp + 10, 3456});
//	emit endInsertRows();
////	emit dataChanged(createIndex(0, 0), createIndex(m_data.count() - 1, columnCount() - 1));
//	return;

	if (data.count() > m_data.count()) {
		emit beginInsertRows(QModelIndex(), m_data.count(), data.count() - 1);
		m_data = data;
		qDebug("data size after set %d", m_data.size());
		emit endInsertRows();
		emit dataChanged(createIndex(0, 0), createIndex(m_data.count() - 1, columnCount() - 1));
	} else if (data.count() < m_data.count()) {
		emit beginRemoveRows(QModelIndex(), data.count(), m_data.count() - 1);
		m_data = data;
		emit endRemoveRows();
		emit dataChanged(createIndex(0, 0), createIndex(m_data.count() - 1, columnCount() - 1));
	} else {
		m_data = data;
		emit dataChanged(createIndex(0, 0), createIndex(m_data.count() - 1, columnCount() - 1));
	}
}

}
}
