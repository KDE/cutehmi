#include "../../include/cutehmi/XMLBackendPlugin.hpp"

namespace cutehmi {
namespace base {

XMLBackendPlugin::XMLBackendPlugin(IXMLBackendPlugin * implementation, QObject * parent):
	QObject(parent),
	m(new Members{implementation})
{
}

IXMLBackendPlugin * XMLBackendPlugin::implementation()
{
	return m->implementation;
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
