#ifndef RECENCYCOLLECTIVE_HPP
#define RECENCYCOLLECTIVE_HPP

#include "common.hpp"
#include "TagCache.hpp"
#include "RecencyTable.hpp"
#include "TableCollective.hpp"

namespace cutehmi {
namespace dataacquisition {
namespace internal {

class CUTEHMI_DATAACQUISITION_PRIVATE RecencyCollective:
	public TableCollective
{
		Q_OBJECT

	public:
		RecencyCollective();

		void update(const RecencyTable<int>::TuplesContainer & tuples);

		void update(const RecencyTable<bool>::TuplesContainer & tuples);

		void update(const RecencyTable<double>::TuplesContainer & tuples);

	protected:
		void updateSchema(Schema * schema) override;

	private:
		template<typename T>
		void updateTable(const typename RecencyTable<T>::TuplesContainer & tuples, std::unique_ptr<RecencyTable<T>> & table);

		struct Members
		{
			std::unique_ptr<TagCache> tagCache;
			std::unique_ptr<RecencyTable<int>> recencyInt;
			std::unique_ptr<RecencyTable<bool>> recencyBool;
			std::unique_ptr<RecencyTable<double>> recencyReal;
		};

		MPtr<Members> m;
};

}
}
}

#endif // RECENCYCOLLECTIVE_HPP
