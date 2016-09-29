import QtQuick 2.0

//<workaround id="QML_Base-4" target="Qt" cause="QTBUG-34418">
// Singletons require explicit import to load qmldir file.
import "."
//</workaround>

QtObject
{
	property real value
	property color color: implicitColor
	property color implicitColor: Palette.normal
}
