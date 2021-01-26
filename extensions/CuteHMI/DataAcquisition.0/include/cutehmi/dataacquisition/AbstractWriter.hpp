#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_ABSTRACTWRITER_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_ABSTRACTWRITER_HPP

#include "internal/common.hpp"
#include "internal/DbServiceableMixin.hpp"
#include "TagValue.hpp"
#include "Schema.hpp"

#include <cutehmi/services/Serviceable.hpp>

#include <QObject>
#include <QQmlListProperty>

namespace cutehmi {
namespace dataacquisition {

/**
 * Abstract database writer.
 */
class CUTEHMI_DATAACQUISITION_API AbstractWriter:
	public QObject,
	public services::Serviceable
{
		Q_OBJECT

	public:
		Q_PROPERTY(QQmlListProperty<cutehmi::dataacquisition::TagValue> values READ valueList)
		Q_CLASSINFO("DefaultProperty", "values")

		Q_PROPERTY(cutehmi::dataacquisition::Schema * schema READ schema WRITE setSchema NOTIFY schemaChanged)

		AbstractWriter(QObject * parent = nullptr);

		QQmlListProperty<TagValue> valueList();

		Schema * schema() const;

		void setSchema(Schema * schema);

		Q_INVOKABLE TagValue * getValue(int index);

		Q_INVOKABLE void appendValue(cutehmi::dataacquisition::TagValue * value);

		Q_INVOKABLE void clearValues();

	signals:
		void schemaChanged();

	CUTEHMI_PROTECTED_SIGNALS:
		void broke();

		void started();

		void stopped();

		void databaseConnected();

		void schemaValidated();

	protected:
		typedef QList<TagValue *> TagValueContainer;

		const TagValueContainer & values() const;

	private slots:
		void onSchemaValidated(bool result);

	private:
		static int ValueListCount(QQmlListProperty<TagValue> * property);

		static TagValue * ValueListAt(QQmlListProperty<TagValue> * property, int index);

		static void ValueListClear(QQmlListProperty<TagValue> * property);

		static void ValuesListAppend(QQmlListProperty<TagValue> * property, TagValue * value);

		struct Members
		{
			TagValueContainer values;
			QQmlListProperty<TagValue> valueList;
			Schema * schema;

			Members(AbstractWriter * p_parent):
				valueList(p_parent, & values, & AbstractWriter::ValuesListAppend, & AbstractWriter::ValueListCount, & AbstractWriter::ValueListAt, & AbstractWriter::ValueListClear),
				schema(nullptr)
			{
			}
		};

		MPtr<Members> m;
};

}
}

#endif

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
