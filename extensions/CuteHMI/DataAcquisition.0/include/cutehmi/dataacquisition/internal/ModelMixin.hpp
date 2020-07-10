#ifndef MODELMIXIN_HPP
#define MODELMIXIN_HPP

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

#endif // DbServiceableMixin_HPP
