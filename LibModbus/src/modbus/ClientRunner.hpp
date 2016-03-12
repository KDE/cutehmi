#ifndef CUTEHMI_LIBMODBUS_SRC_MODBUS_CLIENTRUNNER_HPP
#define CUTEHMI_LIBMODBUS_SRC_MODBUS_CLIENTRUNNER_HPP

#include "../platform.hpp"
#include "CommunicationThread.hpp"

#include <base/IRunner.hpp>

#include <memory>

namespace cutehmi {
namespace modbus {

class Client;

class CUTEHMI_MODBUS_API ClientRunner:
	public base::IRunner
{
	public:
		ClientRunner(Client * client);

		virtual ~ClientRunner();

		void start() override;

		void stop() override;

	private:
		std::unique_ptr<CommunicationThread> m_thread;
		Client * m_client;
};

}
}

#endif
