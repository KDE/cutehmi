#include "Services.hpp"
#include "IService.hpp"

namespace cutehmi {
namespace base {

void Services::add(IService * service)
{
	m_services.append(service);
}

void Services::clear()
{
	m_services.clear();
}

void Services::start()
{
	for (IService * service : m_services)
		service->start();
}

void Services::stop()
{
	for (IService * service : m_services)
		service->stop();
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
