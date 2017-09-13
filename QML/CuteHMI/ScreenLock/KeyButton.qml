import QtQuick 2.7
import QtQuick.Controls 2.2

AbstractButton {
    id: root
    property Image image
    property alias lockScreen: root.image
    property Timer timer
    property string value: '0'
    property alias radius: button_background.radius
    property bool highlighted: parent.state == "highlighted"

    width: 150
    height: 150

    background: Rectangle {
        id: button_background
        color: "white"
        opacity: 0.0
        radius: root.radius
    }

//    Its position is transformed according to the image
    transform: [
        Scale { origin.x: - root.x; origin.y: - root.y; xScale: image.scale; yScale: image.scale },
        Translate { x: - (image.paintedWidth - image.width) / 2; y: - (image.paintedHeight - image.height) / 2 }
    ]

//    Should be highlighted by default if "highlighted" property is set.
//    Should toggle opacity if It is pressed.
    onHighlightedChanged: { button_background.opacity = (root.highlighted ? 0.4 : 0.0) }
    onPressedChanged: (pressed ^ highlighted) ? button_background.opacity = 0.4 : button_background.opacity = 0.0

//    TODO: move timer.restart() to Its parent slot (e.g. onPassphraseInputChanged)
//    Should append button value to lockScreen.passphraseInput
    onClicked: {
        timer.restart()
        lockScreen.passphraseInput += root.value
    }

//    TODO: create edit passphrase screen
//    When held and unlocked – should enter lockScreen to edit-passphrase state
    onPressAndHold:
    {
        switch (lockScreen.state) {
        case "unlocked":
            lockScreen.state = "edit-passphrase";
            console.log("Entered to change passphrase mode.");
            break;
        case "edit-passphrase":
            console.log("Passphrase edition mode already entered.");
            break;
        default:
            console.log("Unlock screen first.");
        }
    }


}
