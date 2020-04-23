#ifndef DATABASEHANDLER_HPP
#define DATABASEHANDLER_HPP

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

#endif // DATABASEHANDLER_HPP
