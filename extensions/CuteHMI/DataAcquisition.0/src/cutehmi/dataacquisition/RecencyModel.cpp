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
