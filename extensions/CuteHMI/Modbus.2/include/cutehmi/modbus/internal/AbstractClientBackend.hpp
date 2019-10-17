#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_ABSTRACTCLIENTBACKEND_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_ABSTRACTCLIENTBACKEND_HPP

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

#endif
