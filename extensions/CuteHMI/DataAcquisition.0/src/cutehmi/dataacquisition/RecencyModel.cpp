#include <cutehmi/dataacquisition/RecencyModel.hpp>

namespace cutehmi {
namespace dataacquisition {

RecencyModel::RecencyModel(QObject * parent):
	AbstractListModel(parent),
	m(new Members{{}, {}, {}})
{
	connect(this, & RecencyModel::schemaChanged, this, & RecencyModel::onSchemaChanged);
	connect(& m->dbCollective, & internal::RecencyCollective::selected, this, & RecencyModel::onSelected);
	connect(& m->dbCollective, & internal::RecencyCollective::busyChanged, this, & RecencyModel::confirmUpdateFinished);
	connect(& m->dbCollective, & internal::RecencyCollective::errored, this, & RecencyModel::broke);
	connect(& m->dbCollective, & internal::RecencyCollective::busyChanged, this, & RecencyModel::busyChanged);
}

QStringList RecencyModel::tags() const
{
	return m->tags;
}

void RecencyModel::setTags(const QStringList & tags)
{
	if (m->tags != tags) {
		m->tags = tags;
		emit tagsChanged();
	}
}

bool RecencyModel::busy() const
{
	return m->dbCollective.busy();
}

QVariant RecencyModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == TAG_ROLE)
		return m->columnValues.tagName.at(index.row());

	if (role == VALUE_ROLE)
		return m->columnValues.value.at(index.row());

	if (role == TIME_ROLE)
		return m->columnValues.time.at(index.row());

	return QVariant();
}

QHash<int, QByteArray> RecencyModel::roleNames() const
{
	QHash<int, QByteArray> result = Parent::roleNames();
	result[TAG_ROLE] = "tag";
	result[VALUE_ROLE] = "value";
	result[TIME_ROLE] = "time";
	return result;
}

int RecencyModel::rowCount(const QModelIndex & parent) const
{
	if (parent.isValid())
		return 0;

	return m->columnValues.length();
}

void RecencyModel::requestUpdate()
{
	m->dbCollective.select(tags());
}

void RecencyModel::confirmUpdateFinished()
{
	if (!m->dbCollective.busy())
		emit updateFinished();
}

void RecencyModel::onSchemaChanged()
{
	m->dbCollective.setSchema(schema());
}

void RecencyModel::onSelected(internal::RecencyCollective::ColumnValues columnValues)
{
	ModelMixin<RecencyModel>::onSelected(columnValues);
}

}
}
