import qbs

import cutehmi

Project {
	name: "CuteHMI.Examples.Symbols.HVAC.Gallery.0"

	cutehmi.Extension {
		name: parent.name

		vendor: "CuteHMI"

		domain: "cutehmi.kde.org"

		friendlyName: "HVAC Symbols Gallery Example"

		description: "Gallery of HVAC symbols provided by CuteHMI.Symbols.HVAC.0 extension."

		files: [
         "AirFilterSettings.qml",
         "BasicDiscreteInstrumentSettings.qml",
         "BladeDamperSettings.qml",
         "CentrifugalFanSettings.qml",
         "ElementSettings.qml",
         "HeatRecoveryWheelSettings.qml",
         "LICENSE",
         "Main.qml",
         "MotorActuatorSettings.qml",
         "PumpSettings.qml",
         "README.md",
     ]

		Depends { name: "cutehmi.doxygen" }
		cutehmi.doxygen.useDoxyqml: true

		Depends { name: "cutehmi.qmldir" }

		Depends { name: "cutehmi.qmltypes" }

		Depends { name: "cutehmi.view.2" }

		Depends { name: "CuteHMI.Symbols.HVAC.0" }
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
