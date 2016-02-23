#include "ClientRunner.hpp"

namespace cutehmi {
namespace modbus {

ClientRunner::ClientRunner(Client * client):
	m_client(client)
{
}

void ClientRunner::start()
{
	qWarning("clinet runner start() not implemented yet");
}

void ClientRunner::stop()
{
	qWarning("clinet runner stop() not implemented yet");
}

}
}
