#ifndef INCLUDECUTEHMIMODBUSINTERNALTCPCLIENTBACKEND_HPP
#define INCLUDECUTEHMIMODBUSINTERNALTCPCLIENTBACKEND_HPP

#include "QtClientBackend.hpp"
#include "TCPClientConfig.hpp"

#include <QUuid>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * Modbus TCP client backend based on Qt Serial Bus.
 */
class CUTEHMI_MODBUS_PRIVATE QtTCPClientBackend:
	public QtClientBackend
{
		Q_OBJECT

	public:
		QtTCPClientBackend(TCPClientConfig * config, QObject * parent = nullptr);

	protected:
		int slaveAddress() const override;

		void configureConnection() override;

	private:
		struct Members
		{
			TCPClientConfig * config;

			Members(TCPClientConfig * p_config):
				config(p_config)
			{
			}
		};

		MPtr<Members> m;
};

}
}
}

#endif // INCLUDECUTEHMIMODBUSINTERNALTCPCLIENTBACKEND_HPP
