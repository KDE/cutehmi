#ifndef H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_ABSTRACTSERVERBACKEND_HPP
#define H_EXTENSIONS_CUTEHMI_MODBUS_2_INCLUDE_CUTEHMI_MODBUS_INTERNAL_ABSTRACTSERVERBACKEND_HPP

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

#endif

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
