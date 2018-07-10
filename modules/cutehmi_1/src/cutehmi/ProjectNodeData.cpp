#include "../../include/cutehmi/ProjectNodeData.hpp"

namespace cutehmi {

ProjectNodeData::ProjectNodeData(const QString & name):
	m(new Members{name})
{
}

QString ProjectNodeData::name() const
{
	return m->name;
}

void ProjectNodeData::setName(const QString & name)
{
	m->name = name;
}

}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
