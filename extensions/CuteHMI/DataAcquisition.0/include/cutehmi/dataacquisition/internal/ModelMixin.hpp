#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_MODELMIXIN_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_MODELMIXIN_HPP

#include <cutehmi/services/Serviceable.hpp>

#include <cutehmi/shareddatabase/Database.hpp>

#include <QModelIndex>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

template <class DERIVED>
class ModelMixin
{
	protected:
		template <typename COLUMN_VALUES>
		void onSelected(const COLUMN_VALUES & newColumnValues);

	private:
		const DERIVED & derived() const;

		DERIVED & derived();
};

template <typename DERIVED>
template <typename COLUMN_VALUES>
void ModelMixin<DERIVED>::onSelected(const COLUMN_VALUES & newColumnValues)
{
	int newRowCount = newColumnValues.length();
	int currentRowCount = derived().rowCount();
	int changedFrom = -1;
	for (int i = 0; i < std::min(currentRowCount, newRowCount); i++) {
		if (!derived().m->columnValues.isEqual(i, newColumnValues)) {
			if (changedFrom == -1)
				changedFrom = i;
			derived().m->columnValues.replace(i, newColumnValues);
		} else if (changedFrom != -1) {
			emit derived().dataChanged(derived().createIndex(changedFrom, 0), derived().createIndex(i, 0));
			changedFrom = -1;
		}
	}

	if (changedFrom != -1)
		emit derived().dataChanged(derived().createIndex(changedFrom, 0), derived().createIndex(derived().rowCount() - 1, 0));

	if (derived().rowCount() < newRowCount) {
		derived().beginInsertRows(QModelIndex(), derived().rowCount(), newRowCount - 1);
		for (int i = derived().rowCount(); i < newRowCount; i++)
			derived().m->columnValues.insert(i, newColumnValues);
		derived().endInsertRows();
	}

	if (derived().rowCount() > newRowCount) {
		derived().beginRemoveRows(QModelIndex(), newRowCount, derived().rowCount() - 1);
		derived().m->columnValues.eraseFrom(newRowCount);
		derived().endRemoveRows();
	}
}

template <typename DERIVED>
const DERIVED & ModelMixin<DERIVED>::derived() const
{
	return static_cast<const DERIVED &>(*this);
}

template <typename DERIVED>
DERIVED & ModelMixin<DERIVED>::derived()
{
	return static_cast<DERIVED &>(*this);
}

}
}
}

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
