#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_EVENTCOLLECTIVE_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_EVENTCOLLECTIVE_HPP

#include "common.hpp"
#include "TagCache.hpp"
#include "EventTable.hpp"
#include "TableCollective.hpp"

namespace cutehmi {
namespace dataacquisition {

class TagValue;

namespace internal {

class CUTEHMI_DATAACQUISITION_PRIVATE EventCollective:
	public TableCollective
{
		Q_OBJECT

	public:
		EventCollective();

		void insert(const TagValue & tag);

	protected:
		void updateSchema(Schema * schema) override;

	private:
		template <typename T>
		void insertIntoTable(const TagValue & tag, std::unique_ptr<EventTable<T>> & table);

		struct Members
		{
			std::unique_ptr<TagCache> tagCache;
			std::unique_ptr<EventTable<int>> eventInt;
			std::unique_ptr<EventTable<bool>> eventBool;
			std::unique_ptr<EventTable<double>> eventReal;
		};

		MPtr<Members> m;
};

}
}
}

#endif
