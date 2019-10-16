#include <cutehmi/modbus/internal/AbstractServerBackend.hpp>

namespace cutehmi {
namespace modbus {
namespace internal {

AbstractServerBackend::AbstractServerBackend(QObject * parent):
	AbstractDeviceBackend(parent)
{
	connect(this, & AbstractServerBackend::setBusyRequested, this, & AbstractServerBackend::setBusy);
}

}
}
}
