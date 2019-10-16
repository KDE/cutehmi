#include <cutehmi/modbus/Initializer.hpp>
#include <cutehmi/modbus/AbstractDevice.hpp>

namespace cutehmi {
namespace modbus {

Initializer::Initializer():
	ExtensionInitializer<Initializer>(
			[]() {
	qRegisterMetaType<cutehmi::modbus::AbstractDevice::State>();
}
)
{
}

}
}
