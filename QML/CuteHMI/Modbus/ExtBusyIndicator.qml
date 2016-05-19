import QtQuick 2.0
import QtQuick.Controls 1.4

BusyIndicator
{
	x: centerIn === null ? 0.0 : centerIn.mapToItem(parent, centerIn.width / 2.0, centerIn.height / 2.0).x - width / 2.0
	y: centerIn === null ? 0.0 : centerIn.mapToItem(parent, centerIn.width / 2.0, centerIn.height / 2.0).y - height / 2.0
	property Item centerIn
	property var _centeringTrackedObjects: []

	Component.onCompleted: {
		_updateCentering()
		centerInChanged.connect(_updateCentering)
	}

	Component.onDestruction: {
		_disconnectTrackedObjects()
	}

	function center()
	{
		if (centerIn == null)
			return;
		var centerPos = centerIn.mapToItem(parent, centerIn.width / 2.0, centerIn.height / 2.0)
		x = centerPos.x - width / 2.0
		y = centerPos.y - height / 2.0
	}

	function _updateCentering()
	{
		_disconnectTrackedObjects()
		_centeringTrackedObjects = []
		var obj = centerIn
		while (obj != null && obj != parent) {
			obj.xChanged.connect(center)
			obj.yChanged.connect(center)
			obj.parentChanged.connect(_updateCentering)
			_centeringTrackedObjects.push(obj)
			obj = obj.parent
		}
		center()
	}

	function _disconnectTrackedObjects()
	{
		for (var i = 0; i < _centeringTrackedObjects.length; i++) {
			_centeringTrackedObjects[i].xChanged.disconnect(center)
			_centeringTrackedObjects[i].yChanged.disconnect(center)
			_centeringTrackedObjects[i].parentChanged.disconnect(_updateCentering)
		}
	}
}
