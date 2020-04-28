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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
