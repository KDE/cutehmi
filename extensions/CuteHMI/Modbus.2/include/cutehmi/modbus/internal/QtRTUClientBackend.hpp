#ifndef INCLUDECUTEHMIMODBUSINTERNALRTUCLIENTBACKEND_HPP
#define INCLUDECUTEHMIMODBUSINTERNALRTUCLIENTBACKEND_HPP

#include "QtClientBackend.hpp"
#include "RTUClientConfig.hpp"

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * Modbus RTU client backend based on Qt Serial Bus.
 */
class CUTEHMI_MODBUS_PRIVATE QtRTUClientBackend:
	public QtClientBackend
{
		Q_OBJECT

	public:
		QtRTUClientBackend(RTUClientConfig * config, QObject * parent = nullptr);

	protected:
		int slaveAddress() const override;

		void configureConnection() override;

	private:
		struct Members
		{
			RTUClientConfig * config;

			Members(RTUClientConfig * p_config):
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
