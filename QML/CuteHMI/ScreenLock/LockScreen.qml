import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2
import CuteHMI.ScreenLock 1.0

Image
{
    id: root
    property real scale: paintedWidth / sourceSize.width
    property string passphraseInput
    property list<KeyButton> keyButtons
    property alias passphraseTimer: passphraseTimer

    fillMode: Image.PreserveAspectCrop

    states: [
        State { name: "unlocked" },
        State {
            name: "edit-passphrase"
            PropertyChanges { target: root; passphraseInput: "" }
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
        id: passphraseTimer
        interval: 1000
        onTriggered:
        {
            console.log("Inserted passphrase: " + root.passphraseInput);
            switch (root.state) {
            case "edit-passphrase":
                var oldPass = "31415";
                PassphraseInterface.changePassphrase(oldPass, root.passphraseInput);
            }

            if (PassphraseInterface.validatePassphrase(root.passphraseInput)) {
                console.log("Screen unlocked!")
                root.state = "unlocked"
            } else {
                console.log("Wrong passphrase!")
                wrongPassphraseAnimation.restart()
                root.passphraseInput = ""
            }
        }
    }

    SequentialAnimation
    {
        id: wrongPassphraseAnimation
        loops: 4
        property int duration: 10
        property real amplitude: 10.0

        NumberAnimation {
            target: root
            property: "x"
            from: 0
            to: wrongPassphraseAnimation.amplitude
            duration: 2 * wrongPassphraseAnimation.duration
        }

        NumberAnimation {
            target: root
            property: "x"
            from: wrongPassphraseAnimation.amplitude
            to: -wrongPassphraseAnimation.amplitude
            duration: wrongPassphraseAnimation.duration
        }

        NumberAnimation {
            target: root
            property: "x"
            from: -wrongPassphraseAnimation.amplitude
            to: 0
            duration: 2 * wrongPassphraseAnimation.duration
        }
    }

}
