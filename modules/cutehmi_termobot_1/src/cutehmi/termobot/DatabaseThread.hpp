#ifndef H_MODULES_TERMOBOT_DATABASE_THREAD
#define H_MODULES_TERMOBOT_DATABASE_THREAD

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

