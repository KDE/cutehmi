import QtQml 2.2
import QtQuick 2.11
import QtQuick.Controls 2.1
import QtQuick.Extras 1.4

import CuteHMI.Modbus 2.0
import CuteHMI.Services 2.0

/**
  %Main component.
*/
Item {
	width: 640
	height: 480

	Service {
		id: clientService

		name: "Dummy Client"

		DummyClient {
			id: client

			latency: 250
			connectLatency: 0
			disconnectLatency: 0
		}
	}

	Screen {
		anchors.fill: parent
	}

	Component.onCompleted: ServiceManager.start()
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
