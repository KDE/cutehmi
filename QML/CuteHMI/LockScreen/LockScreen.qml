import QtQuick 2.7
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2
import CuteHMI.LockScreen 1.0

Image
{
    id: root
    default property alias keyButtons: buttons.children
    property real scale: paintedWidth / sourceSize.width
    property string passwordInput
    property bool inverted: false
    property alias passwordTimer: passwordTimer

    fillMode: Image.PreserveAspectCrop

    Item
    {
        id: buttons

        transform: [
            Scale { xScale: root.scale; yScale: root.scale },
            Translate { x: - (root.paintedWidth - root.width) / 2; y: - (root.paintedHeight - root.height) / 2 }
        ]

        Component.onCompleted: {
            for (var i = 0; i < children.length; i++)
                if (children[i].valueTriggered) {
                    children[i].valueTriggered.connect(appendValue)
                    children[i].inverted = Qt.binding(function() { return root.inverted })
                }
        }

        function appendValue(value)
        {
            root.passwordInput += value
        }
    }

    Timer
    {
        id: passwordTimer
        interval: 1000
        onTriggered: {
            if (Auth.validatePassword(root.passwordInput)) {
                Auth.locked = false
            } else {
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

    onPasswordInputChanged:
    {
//        Clearing out passwordInput results in stopping timer
        if (passwordInput.length == 0) passwordTimer.stop()
        else passwordTimer.restart()
    }

}
