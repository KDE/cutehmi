#ifndef H_MODULES_CUTEHMI_u_TERMOBOT_u_1_SRC_CUTEHMI_TERMOBOT_PLUGIN_TERMOBOTNODEDATA_HPP
#define H_MODULES_CUTEHMI_u_TERMOBOT_u_1_SRC_CUTEHMI_TERMOBOT_PLUGIN_TERMOBOTNODEDATA_HPP

#include <cutehmi/DataBlock.hpp>

#include "../../../../include/cutehmi/termobot/ContactsModel.hpp"
#include "../../../../include/cutehmi/termobot/DS18B20SettingsModel.hpp"
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

		DS18B20SettingsModel * ds18b20SettingsModel() const;

		Service * service() const;

    private:
		std::unique_ptr<DatabaseThread> m_databaseThread;
		std::unique_ptr<Service> m_service;
		std::unique_ptr<ContactsModel> m_contactsModel;
		std::unique_ptr<DS18B20SettingsModel> m_ds18b20SettingsModel;
};

}
}
}

#endif

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
