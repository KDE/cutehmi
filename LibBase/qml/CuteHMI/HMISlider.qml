import QtQuick 2.0
import QtQuick.Controls 1.4

Slider
{
	id: root

	property alias bindingTarget : binding.target
	property alias dataFormat : binding.property

	Binding {
		id: binding
		property: "int16"
		value: root.value
	}
}
