#ifndef INCLUDECUTEHMIMODBUSINTERNALSERVERBACKEND_HPP
#define INCLUDECUTEHMIMODBUSINTERNALSERVERBACKEND_HPP

#include "common.hpp"
#include "AbstractDeviceBackend.hpp"

#include <cutehmi/InplaceError.hpp>
#include <cutehmi/modbus/AbstractServer.hpp>

#include <QObject>
#include <QUuid>

namespace cutehmi {
namespace modbus {
namespace internal {

/**
 * Abstract server backend. By design backend lives in separate thread, thus communication with backend instances are allowed only
 * through signals & slots mechanism or thread-safe functions.
 */
class CUTEHMI_MODBUS_PRIVATE AbstractServerBackend:
	public AbstractDeviceBackend
{
		Q_OBJECT

	public:
		AbstractServerBackend(QObject * parent = nullptr);

	signals:
		void setBusyRequested(bool busy);

		void busyUpdated(bool busy);

	protected slots:
		virtual void setBusy(bool busy) = 0;
};

}
}
}

#endif // INCLUDECUTEHMIMODBUSINTERNALSERVERBACKEND_HPP
