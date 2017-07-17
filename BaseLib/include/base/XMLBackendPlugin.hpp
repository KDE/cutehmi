#ifndef CUTEHMI_BASELIB_INCLUDE_BASE_XMLBACKENDPLUGIN_HPP
#define CUTEHMI_BASELIB_INCLUDE_BASE_XMLBACKENDPLUGIN_HPP

#include "internal/common.hpp"
#include "IXMLBackendPlugin.hpp"

#include <QObject>

#include <memory>

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API XMLBackendPlugin:
	public QObject
{
	Q_OBJECT

	public:
		explicit XMLBackendPlugin(IXMLBackendPlugin * implementation, QObject * parent = 0);

		IXMLBackendPlugin * implementation();

	private:
		struct Members
		{
			IXMLBackendPlugin * implementation;
		};

		std::unique_ptr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
