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

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
