import qbs

import cutehmi

cutehmi.Test
{
	Depends { name: "CuteHMI.2" }
	Depends { name: "CuteHMI.Test.0" }
}
