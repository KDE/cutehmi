pragma Singleton
import QtQuick 2.0
import CuteHMI.GUI 0.0

QtObject {
	property Theme defaultTheme: Theme {}

	property Theme theme: Theme {}

	property real idle: 0.0

	property bool idleMeasureEnabled: false
}
