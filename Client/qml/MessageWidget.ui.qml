import QtQuick 2.10
import QtQuick.Templates 2.1 as T
import QtQuick.Layouts 1.0

T.Button {
    id: control
    width: 250
    height: 150

    implicitWidth: Math.max(
                       buttonBackground ? buttonBackground.implicitWidth : 0,
                       textItem.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(
                        buttonBackground ? buttonBackground.implicitHeight : 0,
                        textItem.implicitHeight + topPadding + bottomPadding)
    leftPadding: 4
    rightPadding: 4

    text: "My Button"

    background: buttonBackground
    Rectangle {
        id: buttonBackground
        color: "#d4d4d4"
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        radius: 2
        anchors.fill: parent
    }

    Text {
        id: usernamemsg
        x: 8
        y: 0
        text: from
        font.pixelSize: 12
        Layout.preferredHeight: 14
        Layout.preferredWidth: 106
    }

    Text {
        id: dateMsg
        x: 81
        y: 0
        text: date
        font.pixelSize: 12
        Layout.preferredHeight: 14
        Layout.preferredWidth: 105
    }

    Text {
        id: text1
        x: 8
        y: 20
        width: 234
        height: 122
        text: content
        wrapMode: Text.WordWrap
        font.pixelSize: 12
        Layout.preferredHeight: 114
        Layout.preferredWidth: 234
    }

    Rectangle {
        id: rectangle
        x: 42
        y: 36
        width: 200
        height: 200
        color: "#ffffff"
    }

    states: [
        State {
            name: "normal"
            when: !control.down
            PropertyChanges {
                target: buttonBackground
                visible: false
                color: "#d2d2d2"
            }

            PropertyChanges {
                target: username
                color: "#00ff00"
            }

            PropertyChanges {
                target: date
                color: "#6b7376"
            }

            PropertyChanges {
                target: text1
                x: 8
                y: 44
                width: 234
                height: 118
                color: "#6b7376"
                verticalAlignment: Text.AlignTop
                wrapMode: Text.Wrap
                fontSizeMode: Text.Fit
            }

            PropertyChanges {
                target: dateMsg
                x: 171
                y: 16
                color: "#e05141"
            }

            PropertyChanges {
                target: control
                height: 170
            }

            PropertyChanges {
                target: usernamemsg
                x: 55
                y: 16
                color: "#33a5e5"
                font.bold: true
            }

            PropertyChanges {
                target: rectangle
                x: 8
                y: 8
                width: 30
                height: 30
                color: "#676d76"
                radius: 7
                border.color: "#313539"
                border.width: 1
            }
        },
        State {
            name: "down"
            PropertyChanges {
                target: buttonBackground
                visible: false
                color: "#d2d2d2"
            }

            PropertyChanges {
                target: username
                color: "#00ff00"
            }

            PropertyChanges {
                target: date
                color: "#6b7376"
            }

            PropertyChanges {
                target: text1
                x: 8
                y: 44
                width: 234
                height: 118
                color: "#6b7376"
                verticalAlignment: Text.AlignTop
                wrapMode: Text.Wrap
                fontSizeMode: Text.Fit
            }

            PropertyChanges {
                target: dateMsg
                x: 171
                y: 16
                color: "#e05141"
            }

            PropertyChanges {
                target: control
                height: 170
            }

            PropertyChanges {
                target: usernamemsg
                x: 55
                y: 16
                color: "#33a5e5"
                font.bold: true
            }

            PropertyChanges {
                target: rectangle
                x: 8
                y: 8
                width: 30
                height: 30
                color: "#676d76"
                radius: 7
                border.color: "#313539"
                border.width: 1
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.75}
}
##^##*/

