import qbs

import cutehmi

// This file has been initially autogenerated by 'cutehmi.skeleton.cpp' Qbs module.

cutehmi.Test {
	testNamePrefix: parent.parent.name

	Depends { name: "CuteHMI.Workarounds.Qt.labs.settings.1" }
}
