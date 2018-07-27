#ifndef SERVICE_HPP
#define SERVICE_HPP

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

#endif // SERVICE_HPP
