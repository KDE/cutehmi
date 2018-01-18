#ifndef CUTEHMI_AUTHSSHPLUGIN_SRC_AUTHSSH_PLUGIN_AUTHSSHNODEDATA_HPP
#define CUTEHMI_AUTHSSHPLUGIN_SRC_AUTHSSH_PLUGIN_AUTHSSHNODEDATA_HPP

#include <authssh/Client.hpp>

#include <base/DataBlock.hpp>

#include <QObject>

#include <memory>

namespace cutehmi {
namespace authssh {
namespace plugin {

class AuthSSHNodeData:
	public base::DataBlock
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

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
