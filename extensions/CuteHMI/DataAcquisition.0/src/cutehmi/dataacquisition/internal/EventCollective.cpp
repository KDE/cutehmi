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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
