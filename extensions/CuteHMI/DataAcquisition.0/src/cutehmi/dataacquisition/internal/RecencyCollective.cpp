#include <cutehmi/dataacquisition/internal/RecencyCollective.hpp>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

RecencyCollective::RecencyCollective():
	m(new Members)
{
}

void RecencyCollective::update(const RecencyTable<int>::TuplesContainer & tuples)
{
	updateTable(tuples, m->recencyInt);
}

void RecencyCollective::update(const RecencyTable<bool>::TuplesContainer & tuples)
{
	updateTable(tuples, m->recencyBool);
}

void RecencyCollective::update(const RecencyTable<double>::TuplesContainer & tuples)
{
	updateTable(tuples, m->recencyReal);
}

void RecencyCollective::updateSchema(Schema * schema)
{
	m->tagCache.reset(new TagCache(schema));
	m->recencyInt.reset(new RecencyTable<int>(m->tagCache.get(), schema));
	m->recencyBool.reset(new RecencyTable<bool>(m->tagCache.get(), schema));
	m->recencyReal.reset(new RecencyTable<double>(m->tagCache.get(), schema));

	connect(m->tagCache.get(), & DataObject::errored, this, & TableCollective::errored);
	connect(m->recencyInt.get(), & DataObject::errored, this, & TableCollective::errored);
	connect(m->recencyBool.get(), & DataObject::errored, this, & TableCollective::errored);
	connect(m->recencyReal.get(), & DataObject::errored, this, & TableCollective::errored);

	connect(m->tagCache.get(), & DataObject::busyChanged, this, [this, tag = m->tagCache.get()]() {
		accountInsertBusy(tag->busy());
	});
	connect(m->recencyInt.get(), & DataObject::busyChanged, this, [this, recencyInt = m->recencyInt.get()] {
		accountInsertBusy(recencyInt->busy());
	});
	connect(m->recencyBool.get(), & DataObject::busyChanged, this, [this, recencyBool = m->recencyBool.get()] {
		accountInsertBusy(recencyBool->busy());
	});
	connect(m->recencyReal.get(), & DataObject::busyChanged, this, [this, recencyReal = m->recencyReal.get()] {
		accountInsertBusy(recencyReal->busy());
	});
}

template<typename T>
void RecencyCollective::updateTable(const typename RecencyTable<T>::TuplesContainer & tuples, std::unique_ptr<RecencyTable<T>> & table)
{
	if (table)
		table->update(tuples);
	else
		CUTEHMI_CRITICAL("Can not update '" << TableNameTraits<T>::Affixed("recency") << "' table, because table object is not available.");
}

}
}
}
