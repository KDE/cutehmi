#include <cutehmi/dataacquisition/AbstractWriterAttachedType.hpp>

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
