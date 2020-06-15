import qbs

import cutehmi

Project {
	name: "CuteHMI.Modbus.2"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.PuppetExtension {
		originalExtension: parent.name

		files: [
			"puppet/designer/CoilItemSpecifics.qml",
			"puppet/designer/DiscreteInputItemSpecifics.qml",
			"puppet/designer/HoldingRegisterItemSpecifics.qml",
			"puppet/designer/InputRegisterItemSpecifics.qml",
			"puppet/designer/Modbus.metainfo"
		]
	}

	cutehmi.CppExtension {
		name: parent.name

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Modbus"

		description: "Modbus protocol support."

		files: [
			"CoilItem.qml",
			"DiscreteInputItem.qml",
			"HoldingRegisterItem.qml",
			"InputRegisterItem.qml",
			"LICENSE",
			"README.md",
			"RegisterItem.js",
			"dev/CuteHMI.Modbus-1.solved.Qt.design.txt",
			"dev/CuteHMI.Modbus-2.workaround.Qt.design.txt",
			"dev/CuteHMI.Modbus-3.workaround.Qt.design.txt",
			"dev/CuteHMI.Modbus-4.unsolved.Qt.design.txt",
			"dev/CuteHMI.Modbus-5.unsolved.Qt.design.txt",
			"dev/CuteHMI.Modbus-6.unsolved.Qt.design.txt",
			"dev/CuteHMI.Modbus-7.workaround.Qt.design.txt",
			"dev/CuteHMI.Modbus-8.workaround.Qt.design.txt",
			"dev/CuteHMI.Modbus-9.workaround.Qt.design.txt",
			"dev/rationale.txt",
			"include/cutehmi/modbus/AbstractClient.hpp",
			"include/cutehmi/modbus/AbstractDevice.hpp",
			"include/cutehmi/modbus/AbstractRegisterController.hpp",
			"include/cutehmi/modbus/AbstractServer.hpp",
			"include/cutehmi/modbus/Coil.hpp",
			"include/cutehmi/modbus/CoilController.hpp",
			"include/cutehmi/modbus/DiscreteInput.hpp",
			"include/cutehmi/modbus/DiscreteInputController.hpp",
			"include/cutehmi/modbus/DummyClient.hpp",
			"include/cutehmi/modbus/Exception.hpp",
			"include/cutehmi/modbus/HoldingRegister.hpp",
			"include/cutehmi/modbus/HoldingRegisterController.hpp",
			"include/cutehmi/modbus/Init.hpp",
			"include/cutehmi/modbus/InputRegister.hpp",
			"include/cutehmi/modbus/InputRegisterController.hpp",
			"include/cutehmi/modbus/RTUClient.hpp",
			"include/cutehmi/modbus/RTUServer.hpp",
			"include/cutehmi/modbus/Register1.hpp",
			"include/cutehmi/modbus/Register16.hpp",
			"include/cutehmi/modbus/Register16Controller.hpp",
			"include/cutehmi/modbus/Register1Controller.hpp",
			"include/cutehmi/modbus/TCPClient.hpp",
			"include/cutehmi/modbus/TCPServer.hpp",
			"include/cutehmi/modbus/internal/AbstractClientBackend.hpp",
			"include/cutehmi/modbus/internal/AbstractDeviceBackend.hpp",
			"include/cutehmi/modbus/internal/AbstractServerBackend.hpp",
			"include/cutehmi/modbus/internal/Coil.hpp",
			"include/cutehmi/modbus/internal/CoilPolling.hpp",
			"include/cutehmi/modbus/internal/Config.hpp",
			"include/cutehmi/modbus/internal/DataContainer.hpp",
			"include/cutehmi/modbus/internal/DataContainerPolling.hpp",
			"include/cutehmi/modbus/internal/DiscreteInput.hpp",
			"include/cutehmi/modbus/internal/DiscreteInputPolling.hpp",
			"include/cutehmi/modbus/internal/DummyClientBackend.hpp",
			"include/cutehmi/modbus/internal/DummyClientConfig.hpp",
			"include/cutehmi/modbus/internal/HoldingRegister.hpp",
			"include/cutehmi/modbus/internal/HoldingRegisterPolling.hpp",
			"include/cutehmi/modbus/internal/InputRegister.hpp",
			"include/cutehmi/modbus/internal/InputRegisterPolling.hpp",
			"include/cutehmi/modbus/internal/IterableTasks.hpp",
			"include/cutehmi/modbus/internal/PollingIterator.hpp",
			"include/cutehmi/modbus/internal/QtClientBackend.hpp",
			"include/cutehmi/modbus/internal/QtRTUClientBackend.hpp",
			"include/cutehmi/modbus/internal/QtRTUServer.hpp",
			"include/cutehmi/modbus/internal/QtRTUServerBackend.hpp",
			"include/cutehmi/modbus/internal/QtServerBackend.hpp",
			"include/cutehmi/modbus/internal/QtServerMixin.hpp",
			"include/cutehmi/modbus/internal/QtTCPClientBackend.hpp",
			"include/cutehmi/modbus/internal/QtTCPServer.hpp",
			"include/cutehmi/modbus/internal/QtTCPServerBackend.hpp",
			"include/cutehmi/modbus/internal/RTUClientConfig.hpp",
			"include/cutehmi/modbus/internal/RTUServerConfig.hpp",
			"include/cutehmi/modbus/internal/RegisterControllerMixin.hpp",
			"include/cutehmi/modbus/internal/RegisterControllerTraits.hpp",
			"include/cutehmi/modbus/internal/RegisterTraits.hpp",
			"include/cutehmi/modbus/internal/TCPClientConfig.hpp",
			"include/cutehmi/modbus/internal/TCPServerConfig.hpp",
			"include/cutehmi/modbus/internal/common.hpp",
			"include/cutehmi/modbus/internal/functions.hpp",
			"include/cutehmi/modbus/internal/platform.hpp",
			"include/cutehmi/modbus/logging.hpp",
			"include/cutehmi/modbus/metadata.hpp",
			"src/cutehmi/modbus/AbstractClient.cpp",
			"src/cutehmi/modbus/AbstractDevice.cpp",
			"src/cutehmi/modbus/AbstractRegisterController.cpp",
			"src/cutehmi/modbus/AbstractServer.cpp",
			"src/cutehmi/modbus/CoilController.cpp",
			"src/cutehmi/modbus/DiscreteInputController.cpp",
			"src/cutehmi/modbus/DummyClient.cpp",
			"src/cutehmi/modbus/HoldingRegisterController.cpp",
			"src/cutehmi/modbus/Init.cpp",
			"src/cutehmi/modbus/InputRegisterController.cpp",
			"src/cutehmi/modbus/RTUClient.cpp",
			"src/cutehmi/modbus/RTUServer.cpp",
			"src/cutehmi/modbus/Register1.cpp",
			"src/cutehmi/modbus/Register16.cpp",
			"src/cutehmi/modbus/Register16Controller.cpp",
			"src/cutehmi/modbus/Register1Controller.cpp",
			"src/cutehmi/modbus/TCPClient.cpp",
			"src/cutehmi/modbus/TCPServer.cpp",
			"src/cutehmi/modbus/internal/AbstractClientBackend.cpp",
			"src/cutehmi/modbus/internal/AbstractDeviceBackend.cpp",
			"src/cutehmi/modbus/internal/AbstractServerBackend.cpp",
			"src/cutehmi/modbus/internal/Coil.cpp",
			"src/cutehmi/modbus/internal/CoilPolling.cpp",
			"src/cutehmi/modbus/internal/Config.cpp",
			"src/cutehmi/modbus/internal/DiscreteInput.cpp",
			"src/cutehmi/modbus/internal/DiscreteInputPolling.cpp",
			"src/cutehmi/modbus/internal/DummyClientBackend.cpp",
			"src/cutehmi/modbus/internal/DummyClientConfig.cpp",
			"src/cutehmi/modbus/internal/HoldingRegister.cpp",
			"src/cutehmi/modbus/internal/HoldingRegisterPolling.cpp",
			"src/cutehmi/modbus/internal/InputRegister.cpp",
			"src/cutehmi/modbus/internal/InputRegisterPolling.cpp",
			"src/cutehmi/modbus/internal/IterableTasks.cpp",
			"src/cutehmi/modbus/internal/PollingIterator.cpp",
			"src/cutehmi/modbus/internal/QMLPlugin.cpp",
			"src/cutehmi/modbus/internal/QMLPlugin.hpp",
			"src/cutehmi/modbus/internal/QtClientBackend.cpp",
			"src/cutehmi/modbus/internal/QtRTUClientBackend.cpp",
			"src/cutehmi/modbus/internal/QtRTUServer.cpp",
			"src/cutehmi/modbus/internal/QtRTUServerBackend.cpp",
			"src/cutehmi/modbus/internal/QtServerBackend.cpp",
			"src/cutehmi/modbus/internal/QtTCPClientBackend.cpp",
			"src/cutehmi/modbus/internal/QtTCPServer.cpp",
			"src/cutehmi/modbus/internal/QtTCPServerBackend.cpp",
			"src/cutehmi/modbus/internal/RTUClientConfig.cpp",
			"src/cutehmi/modbus/internal/RTUServerConfig.cpp",
			"src/cutehmi/modbus/internal/TCPClientConfig.cpp",
			"src/cutehmi/modbus/internal/TCPServerConfig.cpp",
			"src/cutehmi/modbus/internal/functions.cpp",
			"src/cutehmi/modbus/logging.cpp",
		]

		Depends { name: "Qt.concurrent" }

		Depends { name: "Qt.serialbus" }

		Depends { name: "Qt.serialport" }

		Depends { name: "CuteHMI.2" }

		Depends { name: "CuteHMI.Services.2" }

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.warnIfUndocumented: false
		cutehmi.doxygen.useDoxyqml: true
		cutehmi.doxygen.exclude: ['dev', 'puppet', 'tests']

		Depends { name: "cutehmi.init" }

		Depends { name: "cutehmi.metadata" }

		Depends { name: "cutehmi.qmldir" }
		cutehmi.qmldir.exclude: ["^designer/.*", "\.js$"]

		Depends { name: "cutehmi.qmltypes" }

		Export {
			Depends { name: "Qt.serialbus" }

			Depends { name: "Qt.serialport" }

			Depends { name: "CuteHMI.2" }

			Depends { name: "CuteHMI.Services.2" }
		}
	}
}

//(c)C: Copyright © 2019-2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
