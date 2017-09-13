import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2
import CuteHMI.ScreenLock 1.0

Image
{
    id: root
    property real scale: paintedWidth / sourceSize.width
    property string passwordInput
    property list<KeyButton> keyButtons
    property alias passwordTimer: passwordTimer

    fillMode: Image.PreserveAspectCrop

    states: [
        State { name: "unlocked" },
        State {
            name: "edit-password"
            PropertyChanges { target: root; passwordInput: "" }
            PropertyChanges {
                target: buttons
                state: "highlighted"
            }
        }
    ]

    Item
    {
        id: buttons
        states: [
            State { name: "highlighted" }
        ]
        children: keyButtons
    }

    Timer
    {
        id: passwordTimer
        interval: 1000
        onTriggered:
        {
            console.log("Inserted password: " + root.passwordInput);
            switch (root.state) {
            case "edit-password":
                var oldPass = "31415";
                PasswordInterface.changePassword(oldPass, root.passwordInput);
            }

            if (PasswordInterface.validatePassword(root.passwordInput)) {
                console.log("Screen unlocked!")
                root.state = "unlocked"
            } else {
                console.log("Wrong password!")
                wrongPasswordAnimation.restart()
                root.passwordInput = ""
            }
        }
    }

    SequentialAnimation
    {
        id: wrongPasswordAnimation
        loops: 4
        property int duration: 10
        property real amplitude: 10.0

        NumberAnimation {
            target: root
            property: "x"
            from: 0
            to: wrongPasswordAnimation.amplitude
            duration: 2 * wrongPasswordAnimation.duration
        }

        NumberAnimation {
            target: root
            property: "x"
            from: wrongPasswordAnimation.amplitude
            to: -wrongPasswordAnimation.amplitude
            duration: wrongPasswordAnimation.duration
        }

        NumberAnimation {
            target: root
            property: "x"
            from: -wrongPasswordAnimation.amplitude
            to: 0
            duration: 2 * wrongPasswordAnimation.duration
        }
    }

}
