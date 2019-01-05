#ifndef H_EXTENSIONS_CUTEHMI_BITCOINCASH_0_SRC_CUTEHMI_BITCOINCASH_INTERNAL_QMLPLUGIN_HPP
#define H_EXTENSIONS_CUTEHMI_BITCOINCASH_0_SRC_CUTEHMI_BITCOINCASH_INTERNAL_QMLPLUGIN_HPP

#include <QQmlExtensionPlugin>

class QJSEngine;

namespace cutehmi {
namespace bitcoincash {
namespace internal {

class QMLPlugin:
	public QQmlExtensionPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

	public:
		void registerTypes(const char * uri) override;

	private:
//		static QObject * CuteHMIProvider(QQmlEngine * engine, QJSEngine * scriptEngine);
};

}
}
}

#endif

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
