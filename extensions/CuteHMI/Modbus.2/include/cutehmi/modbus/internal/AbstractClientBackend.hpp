#ifndef INCLUDECUTEHMIMODBUSINTERNALABSTRACTCLIENTBACKEND_HPP
#define INCLUDECUTEHMIMODBUSINTERNALABSTRACTCLIENTBACKEND_HPP

#include "common.hpp"
#include "RegisterTraits.hpp"
#include "AbstractDeviceBackend.hpp"

#include <cutehmi/InplaceError.hpp>
#include <cutehmi/modbus/AbstractClient.hpp>

#include <QObject>
#include <QJsonObject>
#include <QUuid>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * Abstract client backend. By design backend lives in separate thread, thus communication with backend instances are allowed only
 * through signals & slots mechanism or thread-safe functions.
 */
class CUTEHMI_MODBUS_PRIVATE AbstractClientBackend:
	public AbstractDeviceBackend
{
		Q_OBJECT

	public:
		AbstractClientBackend(QObject * parent = nullptr);
};

}
}
}

#endif // INCLUDECUTEHMIMODBUSINTERNALABSTRACTCLIENTBACKEND_HPP
