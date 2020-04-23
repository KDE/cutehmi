#include <cutehmi/dataacquisition/AbstractWriter.hpp>

#include <cutehmi/shareddatabase/Database.hpp>

#include <QTimer>

namespace cutehmi {
namespace dataacquisition {

AbstractWriter::AbstractWriter(QObject * parent):
	QObject(parent),
	m(new Members(this))
{
}

QQmlListProperty<TagValue> AbstractWriter::valueList()
{
	return m->valueList;
}

Schema * AbstractWriter::schema() const
{
	return m->schema;
}

void AbstractWriter::setSchema(Schema * schema)
{
	if (m->schema != schema) {
		if (m->schema)
			m->schema->disconnect(this);

		m->schema = schema;
		emit schemaChanged();

		if (m->schema) {
			connect(m->schema, & Schema::validated, this, & AbstractWriter::onSchemaValidated);
			connect(m->schema, & Schema::errored, this, & AbstractWriter::broke);
		}
	}
}

const AbstractWriter::TagValueContainer & AbstractWriter::values() const
{
	return m->values;
}

QState * AbstractWriter::createWaitingForDatabaseConnectedSate(QState * parent, services::Serviceable::ServiceStatuses * statuses, QState * target)
{
	QState * state = new QState(parent);
	connect(state, & QState::entered, [this, state]() {
		if (schema()) {
			QTimer * timer = new QTimer(schema());
			connect(timer, & QTimer::timeout, [this]() {
				if (shareddatabase::Database::IsConnected(schema()->connectionName()))
					emit databaseConnected();
			});
			connect(state, & QState::exited, timer, & QTimer::stop);
			connect(state, & QState::exited, timer, & QObject::deleteLater);
			timer->start(250);
		} else {
			CUTEHMI_CRITICAL("Schema is not set for '" << this << "' object.");
			emit broke();
		}
	});

	if (statuses)
		statuses->insert(state, tr("Waiting for database"));

	if (target)
		state->addTransition(this, & AbstractWriter::databaseConnected, target);

	return state;
}

QState * AbstractWriter::createValidatingSchemaSate(QState * parent, services::Serviceable::ServiceStatuses * statuses, QState * target)
{
	QState * state = new QState(parent);
	connect(state, & QState::entered, this, [this]() {
		if (!schema()) {
			CUTEHMI_CRITICAL("Schema is not set for '" << this << "' object.");
			emit broke();
		} else
			schema()->validate();
	});

	if (statuses)
		statuses->insert(state, tr("Validating schema"));

	if (target)
		state->addTransition(this, & AbstractWriter::schemaValidated, target);

	return state;
}

void AbstractWriter::onSchemaValidated(bool result)
{
	if (result)
		emit schemaValidated();
	else
		emit broke();
}

int AbstractWriter::ValueListCount(QQmlListProperty<TagValue> * property)
{
	return static_cast<TagValueContainer *>(property->data)->count();
}

TagValue * AbstractWriter::ValueListAt(QQmlListProperty<TagValue> * property, int index)
{
	return static_cast<TagValueContainer *>(property->data)->value(index);
}

void AbstractWriter::ValueListClear(QQmlListProperty<TagValue> * property)
{
	AbstractWriter * writer = static_cast<AbstractWriter *>(property->object);
	for (TagValueContainer::const_iterator it = writer->values().begin(); it != writer->values().end(); ++it) {
		(*it)->disconnect(writer);
	}
	static_cast<TagValueContainer *>(property->data)->clear();
}

void AbstractWriter::ValuesListAppend(QQmlListProperty<TagValue> * property, TagValue * value)
{
	static_cast<TagValueContainer *>(property->data)->append(value);
}

}
}
