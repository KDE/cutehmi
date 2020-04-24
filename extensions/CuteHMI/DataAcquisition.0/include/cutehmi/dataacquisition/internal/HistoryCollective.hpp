#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_HISTORYCOLLECTIVE_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_HISTORYCOLLECTIVE_HPP

#include "common.hpp"
#include "TagCache.hpp"
#include "HistoryTable.hpp"
#include "TableCollective.hpp"

namespace cutehmi {
namespace dataacquisition {
namespace internal {

class CUTEHMI_DATAACQUISITION_PRIVATE HistoryCollective:
	public TableCollective
{
		Q_OBJECT

	public:
		HistoryCollective();

		void insert(const HistoryTable<int>::TuplesContainer & tuples);

		void insert(const HistoryTable<bool>::TuplesContainer & tuples);

		void insert(const HistoryTable<double>::TuplesContainer & tuples);

	protected:
		void updateSchema(Schema * schema) override;

	private:
		template<typename T>
		void insertIntoTable(const typename HistoryTable<T>::TuplesContainer & tuples, std::unique_ptr<HistoryTable<T>> & table);

		struct Members
		{
			std::unique_ptr<TagCache> tagCache;
			std::unique_ptr<HistoryTable<int>> historyInt;
			std::unique_ptr<HistoryTable<bool>> historyBool;
			std::unique_ptr<HistoryTable<double>> historyReal;
		};

		MPtr<Members> m;
};

}
}
}

#endif

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
