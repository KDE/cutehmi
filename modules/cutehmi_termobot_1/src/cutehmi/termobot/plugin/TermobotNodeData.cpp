#include "TermobotNodeData.hpp"

namespace cutehmi {
namespace termobot {
namespace plugin {


TermobotNodeData::TermobotNodeData(std::unique_ptr<Service> service, std::unique_ptr<DatabaseThread> databaseThread):
	m_databaseThread(std::move(databaseThread)),
	m_service(std::move(service)),
	m_contactsModel(new ContactsModel(m_databaseThread.get()))
{}

DatabaseThread * TermobotNodeData::databaseThread() const
{
	return m_databaseThread.get();
}

ContactsModel * TermobotNodeData::contactsModel() const
{
	return m_contactsModel.get();
}

Service * TermobotNodeData::service() const
{
	return m_service.get();
}

}
}
}
