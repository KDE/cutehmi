#include <cutehmi/dataacquisition/internal/TableCollective.hpp>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

TableCollective::TableCollective():
	m(new Members)
{
}

Schema * TableCollective::schema() const
{
	return m->schema;
}

void TableCollective::setSchema(Schema * schema)
{
	if (m->schema)
		m->schema->disconnect(this);

	updateSchema(schema);

	m->schema = schema;

	connect(m->schema, & DataObject::errored, this, & TableCollective::errored);
	connect(m->schema, & DataObject::busyChanged, this, [this, schema]() {
		accountInsertBusy(schema->busy());
	});
}

void TableCollective::confirmWorkersFinished()
{
	if (m->insertsBusy == 0)
		emit workersFinished();
}

void TableCollective::accountInsertBusy(bool busy)
{
	if (busy)
		m->insertsBusy++;
	else
		m->insertsBusy--;

	if (m->insertsBusy == 0)
		emit workersFinished();
}

}
}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
