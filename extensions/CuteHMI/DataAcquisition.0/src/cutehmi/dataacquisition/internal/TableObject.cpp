#include <cutehmi/dataacquisition/internal/TableObject.hpp>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

TableObject::TableObject(Schema * schema, QObject * parent):
	DataObject(parent),
	m(new Members{schema})
{
	if (schema)
		setConnectionName(m->schema->connectionName());
}

Schema * TableObject::schema() const
{
	return m->schema;
}

void TableObject::setSchema(Schema * schema)
{
	if (m->schema != schema) {
		m->schema = schema;
		if (schema)
			setConnectionName(m->schema->connectionName());
		emit schemaChanged();
	}
}

QString TableObject::getSchemaName() const
{
	if (m->schema)
		return m->schema->name();

	CUTEHMI_CRITICAL("Schema for object '" << this << "' has not been set.");
	return QString();
}

}
}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
