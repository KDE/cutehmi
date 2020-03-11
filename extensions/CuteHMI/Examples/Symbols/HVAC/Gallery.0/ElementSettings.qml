import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import CuteHMI.GUI 0.0

ColumnLayout {
	Layout.fillWidth: true

	property Element element

	GroupBox {
		Layout.fillWidth: true

		title: qsTr("Common properties")

		ColumnLayout {
			CheckBox {
				text: qsTr("Neutral")

				onCheckedChanged: checked ? element.colorSet = CuteApplication.theme.palette.neutral : element.colorSet = Qt.binding(element.currentStateColorSet)
			}

			CheckBox {
				text: qsTr("Active")

				checked: element.active

				onCheckedChanged: element.active = checked
			}

			CheckBox {
				text: qsTr("Warning")

				checked: element.warning

				onCheckedChanged: element.warning = checked
			}

			CheckBox {
				text: qsTr("Alarm")

				checked: element.alarm

				onCheckedChanged: element.alarm = checked
			}

			CheckBox {
				text: qsTr("Indirect warning")

				checked: element.indirectWarning

				onCheckedChanged: element.indirectWarning = checked
			}

			CheckBox {
				text: qsTr("Indirect alarm")

				checked: element.indirectAlarm

				onCheckedChanged: element.indirectAlarm = checked
			}
		}
	}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
