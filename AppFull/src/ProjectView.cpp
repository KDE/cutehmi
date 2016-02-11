#include "ProjectView.hpp"

#include <base/ProjectModel.hpp>

#include <QMenu>
#include <QContextMenuEvent>

ProjectView::ProjectView(QWidget * parent):
	QTreeView(parent)
{
	setSelectionBehavior(QAbstractItemView::SelectRows);
}

void ProjectView::contextMenuEvent(QContextMenuEvent * event)
{
	QModelIndex indexAtEventPos = indexAt(event->pos());
	if (!model()->hasIndex(indexAtEventPos.row(), 0, indexAtEventPos.parent()))
		return;

	QMenu menu;
	base::ProjectModel::Node * currentNode = static_cast<base::ProjectModel::Node *>(currentIndex().internalPointer());
	QMenu * visitorMenu = nullptr;
	base::ProjectModel::Node::GUIVisitorDelegate::ContextMenuProxy menuProxy(visitorMenu);
	currentNode->guiVisitorDelegate()->visit(menuProxy);
	if (visitorMenu) {
		if (!visitorMenu->actions().isEmpty()) {
			menu.addSeparator();
			menu.addActions(visitorMenu->actions());
		}
	}

	menu.exec(event->globalPos());

	if (visitorMenu)
		delete visitorMenu;
}

