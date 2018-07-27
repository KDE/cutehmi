#ifndef TERMOBOTNODEDATA_HPP
#define TERMOBOTNODEDATA_HPP

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

#endif // TERMOBOTNODEDATA_HPP
