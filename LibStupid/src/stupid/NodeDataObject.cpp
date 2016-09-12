#include "NodeDataObject.hpp"

namespace cutehmi {
namespace stupid {

NodeDataObject::NodeDataObject(std::unique_ptr<Client> client, std::unique_ptr<Service> service, QObject * parent):
	QObject(parent),
	m_client(std::move(client)),
	m_service(std::move(service))
{
}

Client * NodeDataObject::client() const
{
	return m_client.get();
}

Service * NodeDataObject::service() const
{
	return m_service.get();
}

}
}
