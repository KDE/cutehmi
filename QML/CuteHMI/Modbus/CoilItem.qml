import QtQuick 2.0
import QtQuick.Controls 1.3

import CuteHMI.Modbus 1.0

/**
  Modbus coil item. This item is intended to interact with parent item in which it can be placed.
  Parent item must provide following properties:
		- bool checked - this property will be set to @p true or @p false, depending on coil status.
		.
  In addition parent item may provide:
		- signal checkedChanged() - when this signal is emitted a request will be made to update the coil with actual @a parent.checked value.
		.
  */
Item
{
	id: root

	anchors.verticalCenter: parent.verticalCenter
	anchors.horizontalCenter: parent.horizontalCenter

	property alias device: coilController.device
	property alias address: coilController.address
	property alias busy: coilController.busy
	property alias busyIndicator: busyIndicator
	property alias controller: coilController

	ExtBusyIndicator
	{
		id: busyIndicator

		running: coilController.busy
		centerIn: parent
	}

	CoilController
	{
		id: coilController

		delegate: root.parent
		device: root.device
		address: root.address
	}
}

