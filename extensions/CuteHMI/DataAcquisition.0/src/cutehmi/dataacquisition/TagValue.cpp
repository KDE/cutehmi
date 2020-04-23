#include <cutehmi/dataacquisition/TagValue.hpp>

namespace cutehmi {
namespace dataacquisition {

TagValue::TagValue(QObject * parent):
	QObject(parent),
	m(new Members)
{
}

QString TagValue::name() const
{
	return m->name;
}

void TagValue::setName(const QString & name)
{
	if (m->name != name) {
		m->name = name;
		emit nameChanged();
	}
}

QVariant TagValue::value() const
{
	return m->value;
}

void TagValue::setValue(const QVariant & value)
{
	if (m->value != value) {
		m->value = value;
		emit valueChanged();
	}
}

QString TagValue::typeName() const
{
	return m->value.typeName();
}

}
}
