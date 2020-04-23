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
