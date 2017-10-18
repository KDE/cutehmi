#include "AuthSSHNodeData.hpp"

namespace cutehmi {
namespace authssh {
namespace plugin {

AuthSSHNodeData::AuthSSHNodeData(std::unique_ptr<Auth> auth):
	m_auth(std::move(auth))
{
}

Auth * AuthSSHNodeData::auth() const
{
	return m_auth.get();
}

}
}
}

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
