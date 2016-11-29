#include "Project.hpp"

namespace cutehmi {
namespace base {

QString Project::Error::str() const
{
	switch (code()) {
		case FILE_NOT_EXISTS:
			return tr("File does not exist.");
		case FILE_UNABLE_TO_OPEN:
			return tr("Could not open file.");
		case FILE_EMPTY_NAME:
			return tr("Empty file name.");
		default:
			return base::Error::str();
	}
}

Project::Project()
{
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
