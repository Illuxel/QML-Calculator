import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

ToolButton {
    id: styledButton

    property string iconSource: ""

    property real iconW: 24
    property real iconH: 24

    property color textColor: "#e5e5e5"
    property string textButton: ""
    property bool textBold: true

    property bool centered: true
    property real itemSpacing: 0

    property real imageLeftMargin: 5
    property real textLeftMargin: 8

    property color baseColor: "#2e2e2e"

    property real fluentThikness: 1.0

    contentItem: RowLayout {
        spacing: itemSpacing
        Image {
            smooth: false

            source: iconSource

            sourceSize.width: iconW
            sourceSize.height: iconH

            Layout.leftMargin: imageLeftMargin
            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
        }
        Text {
            text: textButton
            color: textColor
            font.bold: textBold
            font.pixelSize: 16
            Layout.leftMargin: textLeftMargin
            Layout.alignment: Qt.AlignLeft
        }
        Item { Layout.fillWidth: centered }
     }
     background: Rectangle {
         color: styledButton.hovered ? Qt.lighter(baseColor, 1.18) : baseColor
         opacity: fluentThikness
         radius: 5
     }
}
