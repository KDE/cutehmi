import QtQuick 2.3
import QtQuick.Controls 2.1
import QtQuick.Window 2.2
import QtCore

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

		Keys.onPressed: (event) => {
			// Toggle full screen.
			if (event.key === Qt.Key_F11) {
				if (mainWindow.visibility != Window.FullScreen) {
					// Store visibility.
					settings.visibility = mainWindow.visibility
					mainWindow.visibility = Window.FullScreen
				} else {
					// Restore visibility or swap to Window.AutomaticVisibility if application was restored to full screen mode on startup.
					//<unsolved id="cutehmi.view.2-2" target="Qt" cause="bug">
					// When changing window visibility in the following manner:
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

		category: "cutehmi.view.4/MainWindow"

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

	function createDialog(message) {
		var messageDialogComponent = Qt.createComponent("MessageDialog.qml")
		if (messageDialogComponent.status === Component.Error)
			console.error(messageDialogComponent.errorString())
		else {
			var messageDialog = messageDialogComponent.createObject(mainWindow, {"message" : message})
			messageDialog.messageChanged.connect(messageDialog.destroy)
			messageDialog.open()
		}
	}

	Component.onCompleted: {
		for (var i = 1; i < Qt.application.arguments.length; i++)
			if (Qt.application.arguments[i] === "--fullscreen")
				mainWindow.visibility = Window.FullScreen

		Messenger.resetAdvertiser(mainWindow)
	}

	onClosing: {
		settings.storeMainWindow()
	}
}

//(c)C: Copyright © 2020-2023, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
