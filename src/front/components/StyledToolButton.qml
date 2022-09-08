import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

ToolButton {
    id: styledButton

    property string iconSource: ""

    property int iconW: 24
    property int iconH: 24

    property string textButton: ""

    property real itemSpacing: 5

    property color textColor: "#e5e5e5"
    property color baseColor: "#2e2e2e"

    property real fluentThikness: 1.0

    contentItem: RowLayout {
        spacing: itemSpacing
        Image {
            source: iconSource

            sourceSize.width: iconW
            sourceSize.height: iconH

            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
            Layout.leftMargin: 5
        }
        Label {
            text: textButton
            color: textColor
            font {
                bold: true
                pixelSize: 16
            }
            Layout.alignment: Qt.AlignLeft
        }
     }
     background: Rectangle {
         color: styledButton.hovered ? Qt.lighter(baseColor, 1.18) : baseColor
         opacity: fluentThikness
         radius: 5
     }
}
