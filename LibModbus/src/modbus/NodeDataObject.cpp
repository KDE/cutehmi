#include "NodeDataObject.hpp"

namespace cutehmi {
namespace modbus {

NodeDataObject::NodeDataObject(std::unique_ptr<Client> client, std::unique_ptr<ClientRunner> clientRunner, QObject * parent):
	QObject(parent),
	m_client(std::move(client)),
	m_clientRunner(std::move(clientRunner))
{
}

Client * NodeDataObject::client() const
{
	return m_client.get();
}

ClientRunner * NodeDataObject::clientRunner() const
{
	return m_clientRunner.get();
}

}
}
