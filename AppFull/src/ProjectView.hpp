#ifndef CUTEHMI_APPFULL_SRC_PROJECTVIEW_HPP
#define CUTEHMI_APPFULL_SRC_PROJECTVIEW_HPP

#include <QTreeView>

namespace cutehmi {

class ProjectView:
	public QTreeView
{
	public:
		explicit ProjectView(QWidget * parent = 0);

		void contextMenuEvent(QContextMenuEvent * event) override;
};

}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
