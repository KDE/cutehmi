#include <cutehmi/services/ServiceListModel.hpp>

namespace cutehmi {
namespace services {

ServiceListModel::ServiceListModel(QObject * parent):
	QAbstractListModel(parent),
	m(new Members)
{
}

ServiceListModel::~ServiceListModel()
{
	clear();
}

int ServiceListModel::rowCount(const QModelIndex & parent) const
{
	if (parent.isValid())
		return 0;

	return m->services.count();
}

QVariant ServiceListModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == NAME_ROLE)
		return m->services.at(index.row())->name();

	if (role == STATUS_ROLE)
		return m->services.at(index.row())->status();

	return QVariant();
}

QHash<int, QByteArray> ServiceListModel::roleNames() const
{
	QHash<int, QByteArray> result = Parent::roleNames();
	result[NAME_ROLE] = "name";
	result[STATUS_ROLE] = "status";
	return result;
}

Service * ServiceListModel::at(int row)
{
	return m->services.at(row);
}

const Service * ServiceListModel::at(int row) const
{
	return m->services.at(row);
}

void ServiceListModel::append(Service * service)
{
	beginInsertRows(QModelIndex(), m->services.count(), m->services.count());
	m->services.append(service);
	endInsertRows();
}

void ServiceListModel::remove(Service * service)
{
	int index = m->services.indexOf(service);

	if (index == -1) {
		CUTEHMI_WARNING("Attempting to remove a service, which is not on the list.");
		return;
	}

	beginRemoveRows(QModelIndex(), index, index);
	m->services.removeAt(index);
	endRemoveRows();
}

void ServiceListModel::clear()
{
	if (m->services.isEmpty())
		return;

	beginRemoveRows(QModelIndex(), 0, m->services.count() - 1);
	m->services.clear();
	endRemoveRows();
}

}
}

//(c)C: Copyright © 2019, Michal Policht <michpolicht@gmail.com>, Mr CuteBOT <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
