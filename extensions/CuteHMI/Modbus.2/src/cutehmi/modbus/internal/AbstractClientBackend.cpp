#include <cutehmi/modbus/internal/AbstractClientBackend.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

AbstractClientBackend::AbstractClientBackend(QObject * parent):
	AbstractDeviceBackend(parent)
{
}

}
}
}
