import qbs

import cutehmi

Project {
	name: "CuteHMI.Examples.Modbus.ClientServer.0"

	cutehmi.Extension {
		type: []

		name: parent.name

		minor: 0

		micro: 0

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Modbus Client and Server Example"

		description: "Example allowing one to interact with Modbus client and server over Modbus TCP protocol."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
         "CoilControl.qml",
         "DeviceControl.qml",
         "DiscreteInputControl.qml",
         "GridLayoutModel.qml",
         "HoldingRegisterControl.qml",
         "InputRegisterControl.qml",
         "LICENSE",
         "Main.qml",
         "README.md",
         "ServiceControl.qml",
         "TCPClientConfiguration.qml",
         "TCPServerConfiguration.qml",
     ]

		Depends { name: "cutehmi.qmldir" }

		Depends { name: "cutehmi_view" }

		Depends { name: "CuteHMI.Modbus.2" }
	}
}

//(c)C: Copyright © 2019, Mr CuteBOT <michpolicht@gmail.com>, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
