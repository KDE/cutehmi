#include "ProjectView.hpp"

#include <base/ProjectModel.hpp>

#include <widgets/UIVisitorDelegate.hpp>

#include <QMenu>
#include <QContextMenuEvent>

namespace cutehmi {

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
	std::unique_ptr<QMenu> visitorMenu;
	widgets::UIVisitorDelegate::ContextMenuProxy menuProxy(visitorMenu);
	base::ProjectModel::Node * currentNode = static_cast<base::ProjectModel::Node *>(currentIndex().internalPointer());
	if (currentNode->visitorDelegate()->ui())
		currentNode->visitorDelegate()->ui()->visit(menuProxy);
	if (visitorMenu) {
		if (!visitorMenu->actions().isEmpty()) {
			menu.addSeparator();
			menu.addActions(visitorMenu->actions());
		}
	}

	menu.exec(event->globalPos());
}

}
