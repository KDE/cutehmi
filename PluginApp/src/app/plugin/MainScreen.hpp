#ifndef CUTEHMI_PLUGINAPP_SRC_APP_PLUGIN_MAINSCREEN_HPP
#define CUTEHMI_PLUGINAPP_SRC_APP_PLUGIN_MAINSCREEN_HPP

#include <QObject>

namespace cutehmi {
namespace app {
namespace plugin {

class MainScreen:
	public QObject
{
	Q_OBJECT

	public:
		MainScreen(const QString & source, QObject * parent = 0);

		Q_INVOKABLE QString source() const;

	private:
		QString m_source;
};

}
}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
