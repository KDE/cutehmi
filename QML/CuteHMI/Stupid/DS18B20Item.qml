import QtQuick 2.0
import QtQuick.Controls 1.3

import CuteHMI.Stupid 1.0

Item
{
	id: root

	anchors.verticalCenter: parent.verticalCenter
	anchors.horizontalCenter: parent.horizontalCenter

//	property alias device: inputRegisterController.device
//	property alias w1Id: inputRegisterController.w1Id
//	property alias encoding: inputRegisterController.encoding
//	property alias valueScale: inputRegisterController.valueScale
//	property alias busy: inputRegisterController.busy
	property alias busyIndicator: busyIndicator
	property alias controller: ds18b20Controller

	BusyIndicator
	{
		id: busyIndicator

		anchors.centerIn: parent
		running: controller.busy
	}

	DS18B20Controller
	{
		id: ds18b20Controller

//		device: root.device
//		address: root.device
//		encoding: root.encoding
//		valueScale: root.valueScale
	}
}
