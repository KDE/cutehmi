import qbs

import cutehmi

cutehmi.Test
{
	testNamePrefix: parent.parent.name

	Depends { name: "CuteHMI.Modbus.2" }
	Depends { name: "CuteHMI.Test.0" }
}
