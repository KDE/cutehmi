import qbs

import cutehmi

cutehmi.QMLPlugin {
	name: "cutehmi_lockscreen_1_qml"

	files: [
        "ChangePasswordWizard.qml",
        "KeyButton.qml",
        "LockScreen.qml",
        "LockScreenPopup.qml",
        "LockScreenSettings.qml",
        "plugins.qmltypes",
        "qmldir",
        "src/CuteHMILockScreenQMLPlugin.cpp",
        "src/CuteHMILockScreenQMLPlugin.hpp",
        "src/cutehmi/lockscreen/qml/Auth.cpp",
        "src/cutehmi/lockscreen/qml/Auth.hpp",
        "src/cutehmi/lockscreen/qml/Settings.cpp",
        "src/cutehmi/lockscreen/qml/Settings.hpp",
    ]

	Depends { name: "cutehmi_1" }
}

