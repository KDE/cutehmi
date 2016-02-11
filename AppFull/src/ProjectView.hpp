#ifndef CUTEHMI_APPFULL_SRC_PROJECTVIEW_HPP
#define CUTEHMI_APPFULL_SRC_PROJECTVIEW_HPP

#include <QTreeView>

class ProjectView:
	public QTreeView
{
	public:
		explicit ProjectView(QWidget * parent = 0);

		void contextMenuEvent(QContextMenuEvent * event) override;
};

#endif
