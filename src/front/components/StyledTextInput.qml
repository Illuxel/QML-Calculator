import QtQuick 2.15
import QtQuick.Controls 2.4

Rectangle {
    id: textInputStyle

    property string textInput: ""
    signal onTextChanged();
    
    property color textColor: "#e5e5e5"
    property real textSize: 34
    property bool textBold: true
    property int maxLength: 16

    property bool inputFocused: false

    property color backColor: "transparent"
    property color hoverColor: "transparent"
    property color borderColor: "white"


    clip: true
    radius: 5

    color: textInputStyle.hovered ? 
        ((hoverColor === "")
            ? Qt.lighter(baseColor, 1.18) : hoverColor) : backColor
    border.color: textInputStyle.hovered ? borderColor : backColor

    TextInput {
        id: textInput
        anchors.fill: parent
        anchors.margins: 1
        clip: true

        text: textInput

        focus: inputFocused
        color: textColor
        font.bold: textBold
        font.pixelSize: textSize
        maximumLength: maxLength

        validator: RegularExpressionValidator { 
            regularExpression: /^[0-9]*$/
        }

        onTextEdited: {
        
        }
    }
}
