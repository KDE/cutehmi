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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
