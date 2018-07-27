#ifndef H_MODULES_CUTEHMI__TERMOBOT__1_SRC_CUTEHMI_TERMOBOT_SERVICE_HPP
#define H_MODULES_CUTEHMI__TERMOBOT__1_SRC_CUTEHMI_TERMOBOT_SERVICE_HPP

#include "../../../include/cutehmi/termobot/internal/common.hpp"
#include "DatabaseThread.hpp"
#include "DatabaseConnectionData.hpp"

#include <cutehmi/services/Service.hpp>

namespace cutehmi {
namespace termobot {

class Service :
    public services::Service
{

    public:
		Service(const QString & name, DatabaseThread * databaseThread, QObject * parent = nullptr);

		~Service() override;

    protected:
        State customStart() override;

        State customStop() override;

	private:
		struct Members
		{
				DatabaseThread * databaseThread;
		};

		MPtr<Members> m;


};

} // namespace termobot
} // namespace cutehmi

#endif

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
