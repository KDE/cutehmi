#ifndef CLIENTRUNNER_H
#define CLIENTRUNNER_H

#include "../platform.hpp"

#include <base/IRunner.hpp>

namespace cutehmi {
namespace modbus {

class Client;

class CUTEHMI_MODBUS_API ClientRunner:
	public base::IRunner
{
	public:
		ClientRunner(Client * client);

		void start() override;

		void stop() override;

	private:
		Client * m_client;
};

}
}

#endif // CLIENTRUNNER_H
