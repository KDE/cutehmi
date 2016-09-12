#ifndef CUTEHMI_LIBSTUPID_SRC_STUPID_SERVICE_HPP
#define CUTEHMI_LIBSTUPID_SRC_STUPID_SERVICE_HPP


#include "../platform.hpp"
#include "CommunicationThread.hpp"

#include <base/IService.hpp>

#include <memory>

namespace cutehmi {
namespace stupid {

class Client;

class CUTEHMI_STUPID_API Service:
	public base::IService
{
	public:
		Service(Client * client);

		virtual ~Service();

		unsigned long sleep() const;

		void setSleep(unsigned long sleep);

		void init() override;

		void start() override;

		void stop() override;

	private:
		std::unique_ptr<CommunicationThread> m_thread;
		Client * m_client;
};

}
}

#endif
