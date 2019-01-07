#include "QMLPlugin.hpp"

#include <cutehmi/bitcoincash/Address.hpp>

#include <QtQml>

namespace cutehmi {
namespace bitcoincash {
namespace internal {

void QMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.BitcoinCash"));

	qmlRegisterType<cutehmi::bitcoincash::Address>(uri, CUTEHMI_BITCOINCASH_MAJOR, 0, "Address");
}

}
}
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
