#ifndef H_EXTENSIONS_CUTEHMI_FILESYSTEM_0_SRC_CUTEHMI_FILESYSTEM_INTERNAL_QMLPLUGIN_HPP
#define H_EXTENSIONS_CUTEHMI_FILESYSTEM_0_SRC_CUTEHMI_FILESYSTEM_INTERNAL_QMLPLUGIN_HPP

#include <QQmlExtensionPlugin>

class QJSEngine;

namespace cutehmi {
namespace filesystem {
namespace internal {

class QMLPlugin:
	public QQmlExtensionPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

	public:
		void registerTypes(const char * uri) override;
};

}
}
}

#endif

//(c)WZ: Copyright © 2019, Wojciech Zygmuntowicz <wzygmuntowicz.zygmuntowicz@gmail.com>. All rights reserved.
//(c)WZ: This file is a part of CuteHMI.
//(c)WZ: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)WZ: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)WZ: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
