#include <cutehmi/dataacquisition/internal/EventCollective.hpp>
#include <cutehmi/dataacquisition/TagValue.hpp>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

EventCollective::EventCollective():
	m(new Members)
{
}

void EventCollective::insert(const TagValue & tag)
{
	switch (tag.value().type()) {
		case QVariant::Int:
			insertIntoTable<int>(tag, m->eventInt);
			break;
		case QVariant::Bool:
			insertIntoTable<bool>(tag, m->eventBool);
			break;
		case QVariant::Double:
			insertIntoTable<double>(tag, m->eventReal);
			break;
		default:
			CUTEHMI_CRITICAL("Unsupported type ('" << tag.value().typeName() << "') provided as a 'value' of 'TagValue' object.");
	}
}

void EventCollective::updateSchema(Schema * schema)
{
	m->tagCache.reset(new TagCache(schema));
	m->eventInt.reset(new EventTable<int>(m->tagCache.get(), schema));
	m->eventBool.reset(new EventTable<bool>(m->tagCache.get(), schema));
	m->eventReal.reset(new EventTable<double>(m->tagCache.get(), schema));

	connect(m->tagCache.get(), & DataObject::errored, this, & EventCollective::errored);
	connect(m->eventInt.get(), & DataObject::errored, this, & EventCollective::errored);
	connect(m->eventBool.get(), & DataObject::errored, this, & EventCollective::errored);
	connect(m->eventReal.get(), & DataObject::errored, this, & EventCollective::errored);

	connect(m->tagCache.get(), & DataObject::busyChanged, this, [this, tag = m->tagCache.get()]() {
		accountInsertBusy(tag->busy());
	});
	connect(m->eventInt.get(), & DataObject::busyChanged, this, [this, eventInt = m->eventInt.get()] {
		accountInsertBusy(eventInt->busy());
	});
	connect(m->eventBool.get(), & DataObject::busyChanged, this, [this, eventBool = m->eventBool.get()] {
		accountInsertBusy(eventBool->busy());
	});
	connect(m->eventReal.get(), & DataObject::busyChanged, this, [this, eventReal = m->eventReal.get()] {
		accountInsertBusy(eventReal->busy());
	});
}

template<typename T>
void EventCollective::insertIntoTable(const TagValue & tag, std::unique_ptr<EventTable<T>> & table)
{
	typedef typename EventTable<T>::Tuple Tuple;

	if (table)
		table->insert(tag.name(), Tuple{tag.value().value<T>(), QDateTime::currentDateTimeUtc()});
	else
		CUTEHMI_CRITICAL("Can not insert into '" << TableNameTraits<T>::Affixed("event") << "' table, because table object is not available.");
}

}
}
}
