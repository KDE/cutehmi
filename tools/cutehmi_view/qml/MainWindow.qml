import QtQuick 2.3
import QtQuick.Controls 2.1
import QtQuick.Window 2.2
import Qt.labs.settings 1.0

import CuteHMI 2.0

ApplicationWindow {
	id: mainWindow

	x: settings.x
	y: settings.y
	width: settings.width
	height: settings.height
	visibility: settings.visibility
	visible: true	// This is required to avoid "Conflicting properties 'visible' and 'visibility' for Window 'root'" warning and to make Window.AutomaticVisibility visibility work.

	FocusScope {
		focus: true

		Keys.onPressed: {
			// Toggle full screen.
			if (event.key === Qt.Key_F11) {
				if (mainWindow.visibility != Window.FullScreen) {
					// Store visibility.
					settings.visibility = mainWindow.visibility
					mainWindow.visibility = Window.FullScreen
				} else {
					// Restore visibility or swap to Window.AutomaticVisibility if application was restored to full screen mode on startup.
					//<unsolved id="cutehmi_view-2" target="Qt" cause="bug">
					// When changing window visiblity in the following manner:
					// Window.Windowed -> Window.Maximized -> Window.FullScreen -> Window.Maximized -> Window.Windowed,
					// window does not return to its original size.
					if (settings.visibility != Window.FullScreen)
						mainWindow.visibility = settings.visibility
					else
						mainWindow.visibility = Window.AutomaticVisibility
					//<unsolved>
				}
			}
		}
	}

	Settings {
		id: settings

		category: "cutehmi_view/MainWindow"

		property int visibility: Window.AutomaticVisibility
		property int x: 0
		property int y: 0
		property int width: 1280
		property int height: 720

		function storeMainWindow() {
			if (mainWindow.visibility === Window.Hidden)
				settings.visibility = Window.AutomaticVisibility
			else
				settings.visibility = mainWindow.visibility
			if (mainWindow.visibility == Window.Windowed) {
				settings.x = mainWindow.x
				settings.y = mainWindow.y
				settings.width = mainWindow.width
				settings.height = mainWindow.height
			}
		}
	}

	Loader {
		anchors.fill: parent
		source: cutehmi_view_initURL
	}

	function createDialog(dialog) {
		var messageDialogComponent = Qt.createComponent("MessageDialog.qml")
		var messageDialog = messageDialogComponent.createObject(mainWindow, {"dialog" : dialog})
		messageDialog.dialogChanged.connect(messageDialog.destroy)
		messageDialog.open()
	}

	Component.onCompleted: {
		for (var i = 1; i < Qt.application.arguments.length; i++)
			if (Qt.application.arguments[i] === "--fullscreen")
				mainWindow.visibility = Window.FullScreen

		Dialogist.resetAdvertiser(mainWindow)
	}

	onClosing: {
		settings.storeMainWindow()
	}
}

//(c)MP: Copyright © 2018-2019, Michal Policht <michpolicht@gmail.com>. All rights reserved.
//(c)MP: This file is a part of CuteHMI.
//(c)MP: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)MP: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)MP: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
