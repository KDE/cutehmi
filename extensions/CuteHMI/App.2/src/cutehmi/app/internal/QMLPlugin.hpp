#ifndef H_QML_CUTEHMI_APP_SRC_CUTEHMIAPPQMLPLUGIN_HPP
#define H_QML_CUTEHMI_APP_SRC_CUTEHMIAPPQMLPLUGIN_HPP

#include <QQmlExtensionPlugin>

class QJSEngine;

namespace cutehmi {
namespace app {
namespace internal {

class QMLPlugin:
	public QQmlExtensionPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

	public:
		void registerTypes(const char * uri) override;

		//<CuteHMI.LockScreen-1.workaround target="Qt" cause="design">
		static QObject * CuteAppProvider(QQmlEngine * engine, QJSEngine * scriptEngine);
		//</CuteHMI.LockScreen-1.workaround>
};


}
}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
