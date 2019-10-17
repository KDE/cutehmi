#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_QTRTUCLIENTBACKEND_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_QTRTUCLIENTBACKEND_HPP

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

#endif
