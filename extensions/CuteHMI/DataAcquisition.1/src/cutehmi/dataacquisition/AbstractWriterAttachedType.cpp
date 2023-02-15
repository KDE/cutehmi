#include "AbstractWriterAttachedType.hpp"

namespace cutehmi {
namespace dataacquisition {

AbstractWriterAttachedType::AbstractWriterAttachedType(QObject * parent):
	QObject(parent),
	m(new Members(this))
{
}

QQmlListProperty<AbstractWriter> AbstractWriterAttachedType::targetList() const
{
	return m->targetList;
}

const AbstractWriterAttachedType::TargetsContainer & AbstractWriterAttachedType::targets() const
{
	return m->targets;
}

AbstractWriterAttachedType::TargetsContainer & AbstractWriterAttachedType::targets()
{
	return m->targets;
}

workarounds::qt5compatibility::sizeType AbstractWriterAttachedType::TargetListCount(QQmlListProperty<AbstractWriter> * property)
{
	return static_cast<TargetsContainer *>(property->data)->count();
}

AbstractWriter * AbstractWriterAttachedType::TargetListAt(QQmlListProperty<AbstractWriter> * property, workarounds::qt5compatibility::sizeType index)
{
	return static_cast<TargetsContainer *>(property->data)->value(index);
}

void AbstractWriterAttachedType::TargetListClear(QQmlListProperty<AbstractWriter> * property)
{
	AbstractWriterAttachedType * attachedType = static_cast<AbstractWriterAttachedType *>(property->object);
	for (TargetsContainer::iterator target = attachedType->targets().begin(); target != attachedType->targets().end(); ++target) {
		TagValue * tagValue = qobject_cast<TagValue *>(attachedType->parent());
		if (*target != nullptr) {
			// There is no operation for removing individual TagValue object, so we need to copy whole list from target, remove the
			// element, clear whole list in the target and add elements one by one.
			AbstractWriter::TagValueContainer newValues = (*target)->values();
			newValues.removeAll(tagValue);
			(*target)->clearValues();
			for (auto && value : newValues)
				(*target)->appendValue(value);
		}
	}

	static_cast<TargetsContainer *>(property->data)->clear();
}

void AbstractWriterAttachedType::TargetListAppend(QQmlListProperty<AbstractWriter> * property, AbstractWriter * value)
{
	AbstractWriterAttachedType * attachedType = static_cast<AbstractWriterAttachedType *>(property->object);
	TagValue * tagValue = qobject_cast<TagValue *>(attachedType->parent());
	if (value != nullptr && tagValue != nullptr) {
		value->appendValue(tagValue);
		static_cast<TargetsContainer *>(property->data)->append(value);
	}
}

}
}

//(c)C: Copyright © 2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
