import QtQuick 2.0
import QtQuick.Controls 1.3

import CuteHMI.Stupid 1.0

Item
{
	id: root

	anchors.verticalCenter: parent.verticalCenter
	anchors.horizontalCenter: parent.horizontalCenter

	property alias busyIndicator: busyIndicator
	property alias controller: controller

	BusyIndicator
	{
		id: busyIndicator

		anchors.centerIn: parent
		running: controller.busy
	}

	DS18B20Controller
	{
		id: controller
	}
}
