import qbs

import cutehmi

Project {
	name: "CuteHMI.Modbus.2"

	references: [
		"tests/tests.qbs"
	]

	cutehmi.Extension {
		name: parent.name

		minor: 0

		micro: 0

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "Modbus"

		description: "Modbus protocol support."

		author: "Michal Policht"

		copyright: "Michal Policht"

		license: "GNU Lesser General Public License, v. 3.0"

		files: [
         "LICENSE",
         "README.md",
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
         "include/cutehmi/modbus/Initializer.hpp",
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
         "qmldir",
         "src/cutehmi/modbus/AbstractClient.cpp",
         "src/cutehmi/modbus/AbstractDevice.cpp",
         "src/cutehmi/modbus/AbstractRegisterController.cpp",
         "src/cutehmi/modbus/AbstractServer.cpp",
         "src/cutehmi/modbus/CoilController.cpp",
         "src/cutehmi/modbus/DiscreteInputController.cpp",
         "src/cutehmi/modbus/DummyClient.cpp",
         "src/cutehmi/modbus/HoldingRegisterController.cpp",
         "src/cutehmi/modbus/Initializer.cpp",
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

		Depends { name: "cutehmi.qmltypes" }

		Depends { name: "cutehmi.init" }
		cutehmi.init.initializerClass: "cutehmi::modbus::Initializer"

		Export {
			Depends { name: "Qt.serialbus" }

			Depends { name: "Qt.serialport" }

			Depends { name: "CuteHMI.2" }

			Depends { name: "CuteHMI.Services.2" }
		}
	}
}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
