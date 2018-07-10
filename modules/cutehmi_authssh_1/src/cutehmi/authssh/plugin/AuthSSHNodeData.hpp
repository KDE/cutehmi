#ifndef H_MODULES_CUTEHMI__AUTHSSH__1_SRC_CUTEHMI_AUTHSSH_PLUGIN_AUTHSSHNODEDATA_HPP
#define H_MODULES_CUTEHMI__AUTHSSH__1_SRC_CUTEHMI_AUTHSSH_PLUGIN_AUTHSSHNODEDATA_HPP

#include "../../../../include/cutehmi/authssh/Client.hpp"


#include <cutehmi/DataBlock.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace authssh {
namespace plugin {

class AuthSSHNodeData:
	public DataBlock
{
	public:
		AuthSSHNodeData(std::unique_ptr<Client> auth);

		~AuthSSHNodeData() override = default;

		Client * auth() const;

	private:
		std::unique_ptr<Client> m_auth;
};

}
}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
