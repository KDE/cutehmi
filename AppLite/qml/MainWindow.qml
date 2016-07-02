import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import Qt.labs.settings 1.0

ApplicationWindow
{
	id: mainWindow
	x: settings.x
	y: settings.y
	width: settings.width
	height: settings.height
	visibility: settings.visibility
	visible: true	// This is required to avoid "Conflicting properties 'visible' and 'visibility' for Window 'root'" warning and to make Window.AutomaticVisibility visibility work.

	FocusScope
	{
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
					//<unsolved id="AppLite-2" target="Qt" cause="bug>
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

	Settings
	{
		id: settings
		category: "MainWindow"
		property int visibility: Window.AutomaticVisibility
		property int x: 0
		property int y: 0
		property int width: 1280
		property int height: 720

		function storeMainWindow()
		{
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


	Loader
	{
		anchors.fill: parent
		source: defaultScreenUrl
	}

	Component.onCompleted: {
		for (var i = 1; i < Qt.application.arguments.length; i++)
			if (Qt.application.arguments[i] === "--fullscreen")
				mainWindow.visibility = Window.FullScreen
	}

	onClosing: {
		settings.storeMainWindow()
	}
}
