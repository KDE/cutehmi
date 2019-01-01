import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1

import CuteHMI.Services 1.0

Item
{
	id: root

	implicitWidth: 400
	implicitHeight: 200

	FontMetrics
	{
		id: fontMetrics
	}

	Component
	{
		id: serviceDelegate

		Item
		{
			width: parent.width
			height: fontMetrics.height

			Text
			{
				anchors.left: parent.left
				text: model.modelData.name
			}

			Text
			{
				anchors.right: parent.right
				text: stateToString(model.modelData.state)
			}

			function stateToString(state)
			{
				switch (state) {
				case Service.STOPPED:
					return "Stopped"
				case Service.STARTED:
					return "Started"
				case Service.STARTING:
					return "Starting..."
				case Service.STOPPING:
					return "Stopping..."
				case Service.BROKEN:
					return "Broken"
				case Service.REPAIRING:
					return "Resuming..."
				default:
					return "Unknown state: " + state
				}
			}
		}
	}

	Rectangle
	{
		id: servicesBackground

		anchors.fill: serviceViewLayout
		anchors.margins: -10
		radius: 5

		color: "#EEEEEE"
		opacity: 0.75
	}

	ColumnLayout
	{
		id: serviceViewLayout

		width: 400
		anchors.centerIn: parent
		spacing: 5.0

		Label
		{
			id: servicesCaption

			text: "Services"
		}

		ListView
		{
			id: servicesView

			Layout.preferredHeight: (fontMetrics.height + spacing) * model.length
			Layout.maximumHeight: root.height - servicesCaption.height + 2 * servicesBackground.anchors.margins - spacing
			Layout.fillWidth: true
			spacing: parent.spacing

			clip: true
			boundsBehavior: Flickable.OvershootBounds
			model: serviceRegistry.serviceList
			delegate: serviceDelegate
			focus: true
		}

		Row
		{
			spacing: 5

			Button
			{
				text: "Start"
				onClicked: serviceRegistry.start()
			}

			Button
			{
				text: "Stop"
				onClicked: serviceRegistry.stop()
			}
		}
	}

	Component.onCompleted: serviceRegistry.start()	// 'serviceRegistry' has been exposed as QML property within 'SampleProject.cutehmi.xml' file.
}

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the DO WHAT THE FUCK YOU WANT TO BUT NO FUCKING WARRANTY PUBLIC LICENSE, Version 1.
//(c)MP: DO WHAT THE FUCK YOU WANT TO BUT NO FUCKING WARRANTY PUBLIC LICENSE TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//(c)MP: 0. You just DO WHAT THE FUCK YOU WANT TO.
//(c)MP: 1. NO FUCKING WARRANTY!
