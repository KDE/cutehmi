#include <cutehmi/dataacquisition/internal/TableObject.hpp>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

TableObject::TableObject(Schema * schema, QObject * parent):
	DataObject(parent),
	m(new Members{schema})
{
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
		setConnectionName(m->schema->connectionName());
		emit schemaChanged();
	}
}

}
}
}
