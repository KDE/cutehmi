#include "../../include/cutehmi/ProjectModel.hpp"

#include <QtDebug>
#include <QQmlContext>
#include <QUuid>

namespace cutehmi {

ProjectModel::ProjectModel(QObject * parent):
	QAbstractItemModel(parent),
	m(new Members)
{
}

QModelIndex ProjectModel::index(int row, int column, const QModelIndex & parent) const
{
	// Return immediately invalid index if column is not 0.
	if (column != 0)
		return QModelIndex();

	ProjectNode * parentNode;
	// No parent. Use root node.
	if (parent == QModelIndex())
		//<workaround id="cutehmi_1-1" target="Qt" cause="design">
		parentNode = const_cast<ProjectNode *>(& m->root);
		//</workaround>
	else
		parentNode = static_cast<ProjectNode *>(parent.internalPointer());

	ProjectNode * child = parentNode->child(row);
	if (child != nullptr)
		return createIndex(row, column, child);

	// If child does not exist return invalid index.
	return QModelIndex();
}

QModelIndex ProjectModel::parent(const QModelIndex & child) const
{
	if (child == QModelIndex())
		return QModelIndex();

	ProjectNode * parentNode = static_cast<ProjectNode *>(child.internalPointer())->parent();
	if (parentNode != nullptr) {
		ProjectNode * grandParentNode = parentNode->parent();
		if (grandParentNode == nullptr)
			return QModelIndex();	// Root node.
		return createIndex(grandParentNode->childIndex(parentNode), 0, parentNode);
	}
	return QModelIndex();
}

int ProjectModel::rowCount(const QModelIndex & parent) const
{
	if (parent == QModelIndex())
		return m->root.countChildren();
	return static_cast<ProjectNode *>(parent.internalPointer())->countChildren();
}

int ProjectModel::columnCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent);

	return 1;
}

QVariant ProjectModel::data(const QModelIndex & index, int role) const
{
	switch (role) {
		//General purpose roles:
		case Qt::DisplayRole:		// "[0] The key data to be rendered in the form of text. (QString)"
			return static_cast<ProjectNode *>(index.internalPointer())->data().name();
		case Qt::DecorationRole:	// "[1] The data to be rendered as a decoration in the form of an icon. (QColor, QIcon or QPixmap)"
			return QVariant();	// This should be provided by extended GUI model.
		case Qt::EditRole:			// "[2] The data in a form suitable for editing in an editor. (QString)"
			return QVariant();	// Not applicable.
//		case Qt::ToolTipRole:		// "[3] The data displayed in the item's tooltip. (QString)"
//			return QVariant();	// Currently no tooltip.
//		case Qt::StatusTipRole:		// "[4] The data displayed in the status bar. (QString)"
//			return QVariant(); // Nothing on status bar.
//		case Qt::WhatsThisRole:		// "[5] The data displayed for the item in "What's This?" mode. (QString)"
//			return QVariant(); // Nothing on what's this.
		case Qt::SizeHintRole:		// "[13] The size hint for the item that will be supplied to views. (QSize)"
			return QVariant(); // No size hint.

		// Appearance and metadata roles:
		case Qt::FontRole:				// "[6] The font used for items rendered with the default delegate. (QFont)"
			return QVariant();	// Use standard font.
		case Qt::TextAlignmentRole:		// "[7] The alignment of the text for items rendered with the default delegate. (Qt::AlignmentFlag)"
			return QVariant();	// Standard text alignment.
		case Qt::BackgroundRole:		// "[8] The background brush used for items rendered with the default delegate. (QBrush)"
			return QVariant();	// No special background.
		case Qt::ForegroundRole:		// "[9] The foreground brush (text color, typically) used for items rendered with the default delegate. (QBrush)"
			return QVariant();	// No special foreground.
		case Qt::CheckStateRole:		// "[10] This role is used to obtain the checked state of an item. (Qt::CheckState)"
			return QVariant();	// Item not checkable.
		case Qt::InitialSortOrderRole:	// "[14] This role is used to obtain the initial sort order of a header view section. (Qt::SortOrder). This role was introduced in Qt 4.8"
			return QVariant();	// Use default sort order.

		// Accessibility roles:
		case Qt::AccessibleTextRole:		// "[11] The text to be used by accessibility extensions and plugins, such as screen readers. (QString)"
			return static_cast<ProjectNode *>(index.internalPointer())->data().name();
//		case Qt::AccessibleDescriptionRole:	// "[12] A description of the item for accessibility purposes. (QString)"
//			return QVariant();	// No description.

		default:
			CUTEHMI_LOG_DEBUG("Data item role (" << role << ") not supported yet.");
	}
	return QVariant();
}

QVariant ProjectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	// Currently only horizontal headers are supported.
	if (orientation != Qt::Horizontal)
		return QVariant();

	// Currently only single column is used.
	if (section != 0)
		return QVariant();

	switch (role) {
		//General purpose roles:
		case Qt::DisplayRole:		// "[0] The key data to be rendered in the form of text. (QString)"
			return m->root.data().name();
		case Qt::DecorationRole:	// "[1] The data to be rendered as a decoration in the form of an icon. (QColor, QIcon or QPixmap)"
			return QVariant();	// This may be provided in future.
		case Qt::EditRole:			// "[2] The data in a form suitable for editing in an editor. (QString)"
			return QVariant();	// Not applicable.
//		case Qt::ToolTipRole:		// "[3] The data displayed in the item's tooltip. (QString)"
//			return QVariant();	// Currently no tooltip.
//		case Qt::StatusTipRole:		// "[4] The data displayed in the status bar. (QString)"
//			return QVariant(); // Nothing on status bar.
//		case Qt::WhatsThisRole:		// "[5] The data displayed for the item in "What's This?" mode. (QString)"
//			return QVariant(); // Nothing on what's this.
		case Qt::SizeHintRole:		// "[13] The size hint for the item that will be supplied to views. (QSize)"
			return QVariant(); // No size hint.

		// Appearance and metadata roles:
		case Qt::FontRole:				// "[6] The font used for items rendered with the default delegate. (QFont)"
			return QVariant();	// Use standard font.
		case Qt::TextAlignmentRole:		// "[7] The alignment of the text for items rendered with the default delegate. (Qt::AlignmentFlag)"
			return QVariant();	// Standard text alignment.
		case Qt::BackgroundRole:		// "[8] The background brush used for items rendered with the default delegate. (QBrush)"
			return QVariant();	// No special background.
		case Qt::ForegroundRole:		// "[9] The foreground brush (text color, typically) used for items rendered with the default delegate. (QBrush)"
			return QVariant();	// No special foreground.
		case Qt::CheckStateRole:		// "[10] This role is used to obtain the checked state of an item. (Qt::CheckState)"
			return QVariant();	// Item not checkable.
		case Qt::InitialSortOrderRole:	// "[14] This role is used to obtain the initial sort order of a header view section. (Qt::SortOrder). This role was introduced in Qt 4.8"
			return QVariant();	// Use default sort order.

		// Accessibility roles:
		case Qt::AccessibleTextRole:		// "[11] The text to be used by accessibility extensions and plugins, such as screen readers. (QString)"
			return m->root.data().name();
//		case Qt::AccessibleDescriptionRole:	// "[12] A description of the item for accessibility purposes. (QString)"
//			return QVariant();	// No description.

		default:
			CUTEHMI_LOG_DEBUG("Header item role (" << role << ") not supported yet.");
	}
	return QVariant();
}

Qt::ItemFlags ProjectModel::flags(const QModelIndex & index) const
{
	Q_UNUSED(index);

	// Flags according to Qt documentation:
	//	Qt::NoItemFlags				0	It does not have any properties set.
	//	Qt::ItemIsSelectable		1	It can be selected.
	//	Qt::ItemIsEditable			2	It can be edited.
	//	Qt::ItemIsDragEnabled		4	It can be dragged.
	//	Qt::ItemIsDropEnabled		8	It can be used as a drop target.
	//	Qt::ItemIsUserCheckable		16	It can be checked or unchecked by the user.
	//	Qt::ItemIsEnabled			32	The user can interact with the item.
	//	Qt::ItemIsTristate			64	The item can show three separate states. This enables automatic management of the state of parent items in QTreeWidget (checked if all children are checked, unchecked if all children are unchecked, or partially checked if only some children are checked).
	//	Qt::ItemNeverHasChildren	128	The item never has child items.
	//	Qt::ItemIsUserTristate		256	The user can cycle through three separate states. This value has been added in Qt 5.5.

	// Default implementation returns Qt::ItemIsSelectable | Qt::ItemIsEnabled.

	Qt::ItemFlags flags = Qt::ItemIsSelectable	| Qt::ItemIsEnabled;

	ProjectNode * node = static_cast<ProjectNode *>(index.internalPointer());
	if (node->isLeaf())
		flags |= Qt::ItemNeverHasChildren;

	return flags;
}

ProjectModel::iterator ProjectModel::begin()
{
	return iterator(& m->root);
}

ProjectModel::const_iterator ProjectModel::begin() const
{
	return const_iterator(& m->root);
}

ProjectModel::iterator ProjectModel::end()
{
	return iterator();
}

ProjectModel::const_iterator ProjectModel::end() const
{
	return const_iterator();
}

const ProjectNode & ProjectModel::root() const
{
	return m->root;
}

ProjectNode & ProjectModel::root()
{
	return m->root;
}

QModelIndex ProjectModel::createIndex(int row, int column, ProjectNode * ptr) const
{
	return QAbstractItemModel::createIndex(row, column, ptr);
}

const ProjectNode * ProjectModel::rootPtr() const
{
	return & m->root;
}

ProjectModel::Members::Members():
	root("root", ProjectNodeData("Root node"), std::unique_ptr<ProjectNode::ChildrenContainer>(new ProjectNode::ChildrenContainer))
{
}

}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
