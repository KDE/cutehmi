import QtQuick.Controls 2.12

Container {
	property string text: ""

	property bool autoAccept: true

	property bool discretion: true

	signal accepted()

	function reset() {
		text = ""
	}

	function accept() {
		accepted()
	}
}
