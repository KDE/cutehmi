#include "../../../include/cutehmi/app/MainScreen.hpp"

namespace cutehmi {
namespace app {

MainScreen::MainScreen(const QString & source, QObject * parent):
	QObject(parent),
	m_source(source)
{
}

QString MainScreen::source() const
{
	return m_source;
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
