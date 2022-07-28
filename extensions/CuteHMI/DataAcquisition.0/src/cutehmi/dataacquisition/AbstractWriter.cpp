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

TagValue * AbstractWriter::getValue(int index)
{
	return ValueListAt(& m->valueList, index);
}

void AbstractWriter::appendValue(TagValue * value)
{
	ValuesListAppend(& m->valueList, value);
}

void AbstractWriter::clearValues()
{
	ValueListClear(& m->valueList);
}

const AbstractWriter::TagValueContainer & AbstractWriter::values() const
{
	return m->values;
}

void AbstractWriter::onSchemaValidated(bool result)
{
	if (result)
		emit schemaValidated();
	else
		emit broke();
}

workarounds::qt5compatibility::sizeType AbstractWriter::ValueListCount(QQmlListProperty<TagValue> * property)
{
	return static_cast<TagValueContainer *>(property->data)->count();
}

TagValue * AbstractWriter::ValueListAt(QQmlListProperty<TagValue> * property, workarounds::qt5compatibility::sizeType index)
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

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
