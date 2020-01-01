import qbs

import cutehmi

Project {
	name: "CuteHMI.Examples.Modbus.Requests.0"

	cutehmi.Extension {
		name: parent.name

		minor: 0

		micro: 0

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Modbus Requests Example"

		description: "Example demonstrating a variety of Modbus requests."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
			"DeviceControl.qml",
			"DiagnosticsControl.qml",
			"FetchCommEventCounterControl.qml",
			"FetchCommEventLogControl.qml",
			"LICENSE",
			"Main.qml",
			"MaskWrite4xRegisterControl.qml",
			"README.md",
			"ReadCoilsControl.qml",
			"ReadDiscreteInputsControl.qml",
			"ReadExceptionStatusControl.qml",
			"ReadFIFOQueueControl.qml",
			"ReadFileRecordControl.qml",
			"ReadHoldingRegistersControl.qml",
			"ReadInputRegistersControl.qml",
			"ReadWriteMultipleHoldingRegistersControl.qml",
			"ReportSlaveIdControl.qml",
			"TCPClientConfiguration.qml",
			"TCPServerConfiguration.qml",
			"WriteCoilControl.qml",
			"WriteDiscreteInputControl.qml",
			"WriteFileRecordControl.qml",
			"WriteHoldingRegisterControl.qml",
			"WriteInputRegisterControl.qml",
			"WriteMultipleCoilsControl.qml",
			"WriteMultipleDiscreteInputsControl.qml",
			"WriteMultipleHoldingRegistersControl.qml",
			"WriteMultipleInputRegistersControl.qml",
		]

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.useDoxyqml: true

		Depends { name: "cutehmi.qmldir" }

		Depends { name: "cutehmi.qmltypes" }

		Depends { name: "cutehmi.view.2" }

		Depends { name: "CuteHMI.Modbus.2" }
	}
}

//(c)C: Copyright © 2019, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
