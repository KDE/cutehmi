#ifndef H_MODULES_CUTEHMI__TERMOBOT__1_SRC_CUTEHMI_TERMOBOT_PLUGIN_TERMOBOTNODEDATA_HPP
#define H_MODULES_CUTEHMI__TERMOBOT__1_SRC_CUTEHMI_TERMOBOT_PLUGIN_TERMOBOTNODEDATA_HPP

#include <cutehmi/DataBlock.hpp>

#include "../../../../include/cutehmi/termobot/ContactsModel.hpp"
#include "../Service.hpp"
#include "../DatabaseConnectionData.hpp"
#include "../DatabaseThread.hpp"

namespace cutehmi {
namespace termobot {
namespace plugin {

class TermobotNodeData : public DataBlock
{
    public:
		TermobotNodeData(std::unique_ptr<Service> service, std::unique_ptr<DatabaseThread> databaseThread);

		DatabaseThread * databaseThread() const;

        ContactsModel * contactsModel() const;

		Service * service() const;

    private:
		std::unique_ptr<DatabaseThread> m_databaseThread;
		std::unique_ptr<Service> m_service;
		std::unique_ptr<ContactsModel> m_contactsModel;
};

}
}
}

#endif

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
