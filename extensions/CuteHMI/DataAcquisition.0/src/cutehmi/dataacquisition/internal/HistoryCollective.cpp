#include <cutehmi/dataacquisition/internal/HistoryCollective.hpp>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

HistoryCollective::HistoryCollective():
	m(new Members)
{
}

void HistoryCollective::insert(const HistoryTable<int>::TuplesContainer & tuples)
{
	insertIntoTable(tuples, m->historyInt);
}

void HistoryCollective::insert(const HistoryTable<bool>::TuplesContainer & tuples)
{
	insertIntoTable(tuples, m->historyBool);
}

void HistoryCollective::insert(const HistoryTable<double>::TuplesContainer & tuples)
{
	insertIntoTable(tuples, m->historyReal);
}

void HistoryCollective::updateSchema(Schema * schema)
{
	m->tagCache.reset(new TagCache(schema));
	m->historyInt.reset(new HistoryTable<int>(m->tagCache.get(), schema));
	m->historyBool.reset(new HistoryTable<bool>(m->tagCache.get(), schema));
	m->historyReal.reset(new HistoryTable<double>(m->tagCache.get(), schema));

	connect(m->tagCache.get(), & DataObject::errored, this, & TableCollective::errored);
	connect(m->historyInt.get(), & DataObject::errored, this, & TableCollective::errored);
	connect(m->historyBool.get(), & DataObject::errored, this, & TableCollective::errored);
	connect(m->historyReal.get(), & DataObject::errored, this, & TableCollective::errored);

	connect(m->tagCache.get(), & DataObject::busyChanged, this, [this, tag = m->tagCache.get()]() {
		accountInsertBusy(tag->busy());
	});
	connect(m->historyInt.get(), & DataObject::busyChanged, this, [this, historyInt = m->historyInt.get()] {
		accountInsertBusy(historyInt->busy());
	});
	connect(m->historyBool.get(), & DataObject::busyChanged, this, [this, historyBool = m->historyBool.get()] {
		accountInsertBusy(historyBool->busy());
	});
	connect(m->historyReal.get(), & DataObject::busyChanged, this, [this, historyReal = m->historyReal.get()] {
		accountInsertBusy(historyReal->busy());
	});
}

template<typename T>
void HistoryCollective::insertIntoTable(const typename HistoryTable<T>::TuplesContainer & tuples, std::unique_ptr<HistoryTable<T>> & table)
{
	if (table)
		table->insert(tuples);
	else
		CUTEHMI_CRITICAL("Can not insert into '" << TableNameTraits<T>::Affixed("history") << "' table, because table object is not available.");
}

}
}
}
