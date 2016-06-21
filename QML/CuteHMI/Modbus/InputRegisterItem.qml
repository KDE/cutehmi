import QtQuick 2.0
import QtQuick.Controls 1.3

import CuteHMI.Modbus 1.0

Item
{
	id: root

	anchors.verticalCenter: parent.verticalCenter
	anchors.horizontalCenter: parent.horizontalCenter

	property alias device: inputRegisterController.device
	property alias address: inputRegisterController.address
	property alias encoding: inputRegisterController.encoding
	property alias valueScale: inputRegisterController.valueScale
	property alias busy: inputRegisterController.busy
	property alias busyIndicator: busyIndicator
	property alias controller: inputRegisterController

	ExtBusyIndicator
	{
		id: busyIndicator

		anchors.centerIn: parent
		running: root.busy
	}

	InputRegisterController
	{
		id: inputRegisterController

		device: root.device
		address: root.device
		encoding: root.encoding
		valueScale: root.valueScale
	}
}
