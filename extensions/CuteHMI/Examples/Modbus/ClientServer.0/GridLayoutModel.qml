import QtQml 2.2
import QtQuick 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1
import QtQml.Models 2.1

ObjectModel {
	property GridLayout layout

	Component.onCompleted: {
		for (var i = 0; i < root.count; i++)
			layout.children.push(root.get(i))
	}
}
