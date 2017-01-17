#ifndef CUTEHMI_QML_CUTEHMI_BASE_SRC_CUTEHMIBASEQMLPLUGIN_HPP
#define CUTEHMI_QML_CUTEHMI_BASE_SRC_CUTEHMIBASEQMLPLUGIN_HPP

#include <QQmlExtensionPlugin>

class QJSEngine;

class CuteHMIBaseQMLPlugin:
	public QQmlExtensionPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

	public:
		void registerTypes(const char * uri) override;

	private:
		static QObject * ServiceRegistryProvider(QQmlEngine * engine, QJSEngine * scriptEngine);
};

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
