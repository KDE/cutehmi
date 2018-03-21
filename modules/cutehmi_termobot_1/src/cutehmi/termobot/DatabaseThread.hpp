#ifndef H_MODULES_CUTEHMI__TERMOBOT__1_SRC_CUTEHMI_TERMOBOT_DATABASETHREAD_HPP
#define H_MODULES_CUTEHMI__TERMOBOT__1_SRC_CUTEHMI_TERMOBOT_DATABASETHREAD_HPP

#include "../../../include/cutehmi/termobot/internal/common.hpp"

#include "DatabaseConnectionData.hpp"

#include <cutehmi/Worker.hpp>
#include <cutehmi/ErrorInfo.hpp>

#include <QThread>

#include <memory>

namespace cutehmi {
namespace termobot {

class DatabaseThread:
        public QThread
{
    Q_OBJECT

    public:
        struct CUTEHMI_TERMOBOT_API Error:
            public cutehmi::Error
        {
            enum : int {
                NOT_CONFIGURED = Error::SUBCLASS_BEGIN,
                UNABLE_TO_CONNECT
            };

            using cutehmi::Error::Error;

            QString str() const;
        };

		DatabaseThread(std::unique_ptr<DatabaseConnectionData> dbData);

        DatabaseConnectionData * dbData() const;

    signals:
        void error(cutehmi::ErrorInfo errInfo);

        void connected();

        void disconnected();

    protected:
        void run() override;

    private:
        struct Members
        {
            std::unique_ptr<DatabaseConnectionData> dbData;
            QMutex runLock;
        };

        MPtr<Members> m;
};

}
}

#endif

//(c)WZ: Copyright © 2018, Wojciech Zygmuntowicz. All rights reserved.
//(c)WZ: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
