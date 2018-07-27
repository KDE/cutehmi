#include "TermobotNodeData.hpp"

namespace cutehmi {
namespace termobot {
namespace plugin {


TermobotNodeData::TermobotNodeData(std::unique_ptr<Service> service, std::unique_ptr<DatabaseThread> databaseThread):
	m_databaseThread(std::move(databaseThread)),
	m_service(std::move(service)),
	m_contactsModel(new ContactsModel(m_databaseThread.get()))
{}

DatabaseThread * TermobotNodeData::databaseThread() const
{
	return m_databaseThread.get();
}

ContactsModel * TermobotNodeData::contactsModel() const
{
	return m_contactsModel.get();
}

Service * TermobotNodeData::service() const
{
	return m_service.get();
}

}
}
}

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
