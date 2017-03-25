#include "../../include/stupid/StupidNodeData.hpp"

namespace cutehmi {
namespace stupid {

StupidNodeData::StupidNodeData(std::unique_ptr<Client> client, std::unique_ptr<Service> service, QObject * parent):
	QObject(parent),
	m_client(std::move(client)),
	m_service(std::move(service))
{
}

Client * StupidNodeData::client() const
{
	return m_client.get();
}

Service * StupidNodeData::service() const
{
	return m_service.get();
}

}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
