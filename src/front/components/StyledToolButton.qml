import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

ToolButton {
    id: styledButton

    property string iconSource: ""

    property real iconW: 24
    property real iconH: 24

    property color textColor: "#e5e5e5"
    property color baseColor: "#2e2e2e"
    property color hoverColor: "#2e2e2e"

    property string textButton: ""
    property int textFontSize: 16
    property bool textBold: true

    // margins
    property real imageLeftMargin: 0

    property int imageAlign: Qt.AlignLeft
    property bool fillImageWidth: false
    property bool fillImageHeight: false

    // margins
    property real textLeftMargin: 0

    property int textAlign: Qt.AlignLeft
    property bool fillTextWidth: false
    property bool fillTextHeight: false

    property real contentSpacing: 0

    property real fluentThikness: 1.0

    contentItem: RowLayout {
        spacing: contentSpacing
        Item { Layout.fillWidth: fillImageWidth; }
        Image {
            smooth: false
            source: iconSource
            sourceSize.width: iconW
            sourceSize.height: iconH
            Layout.leftMargin: imageLeftMargin
            Layout.alignment: imageAlign
            Layout.fillHeight: fillImageHeight
        }
        Item { Layout.fillWidth: fillImageWidth; }

        Item { Layout.fillWidth: fillTextWidth; }
        Text {
            text: textButton
            color: textColor
            font.bold: textBold
            font.pixelSize: textFontSize
            Layout.leftMargin: textLeftMargin
            Layout.alignment: textAlign
            Layout.fillHeight: fillTextHeight
        }
        Item { Layout.fillWidth: fillTextWidth; }
     }
     background: Rectangle {
         color: styledButton.hovered ? Qt.lighter(baseColor, 1.18) : baseColor
         opacity: fluentThikness
         radius: 5
     }
}
