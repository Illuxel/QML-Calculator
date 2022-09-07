import QtQuick 2.15
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import "../components" as CalculatorComponents
import Calculator.Standart 1.0

Page {
	id: page

    Standart {
        id: calcStandart

        onPrevValueChanged: 
            prevTextInput.text = calcStandart.prevOperation

        onFinalValueChanged: 
            lastTextInput.text = calcStandart.finalValue
    }
    background: Rectangle {
        color: "transparent"
    }
    ColumnLayout {
        anchors.fill: parent
        spacing: 6
        // last operation
        Rectangle {
            id: prevTextInputStyle
            Layout.fillWidth: true
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            Layout.minimumHeight: parent.height * 0.06
            Layout.alignment: Qt.AlignCenter
            clip: true
            color: "transparent"
            TextInput {
                id: prevTextInput
                anchors.fill: parent
                horizontalAlignment: Qt.AlignRight
                verticalAlignment: Qt.AlignBottom
                readOnly: true
                clip: true
                color: Qt.darker("#e5e5e5", 0.4)
                font.bold: true
                font.pixelSize: 17
            }
        }
        // text input
        Rectangle {
            id: lastTextInputStyle
            Layout.fillWidth: true
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            Layout.minimumHeight: parent.height * 0.14
            Layout.alignment: Qt.AlignCenter
            clip: true
            color: "transparent"
            TextInput {
                id: lastTextInput
                anchors.fill: parent
                horizontalAlignment: Qt.AlignRight
                verticalAlignment: Qt.AlignBottom
                clip: true
                readOnly: true
                color: "#e5e5e5"
                font.bold: true
                font.pixelSize: 34
                maximumLength: 15
            }
        }
        // grid buttons view
        Rectangle {
            id: gridInputStyle
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
            GridView {
                id: gridView
                anchors.fill: parent
                anchors.margins: 10

                cellHeight: gridView.height / 6
                cellWidth: gridView.width / 4

                delegate: CalculatorComponents.StyledToolButton {
                    height: 48
                    width: 72
                    iconH: 1
                    iconW: 1
                    fluentThikness: 0.89
                    itemSpacing: 8
                    textButton: name
                    baseColor: (color == "")
                        ? CalculatorComponents.StyledToolButton.baseColor : color

                    onClicked:
                        calcStandart.processButton(type, func, name);
                }
                model: ListModel {
                    ListElement { name: "%";    type: "function";   func: "%1/100";               color: "" }
                    ListElement { name: "CE";   type: "cmd";        func: "clrall";          color: "" }
                    ListElement { name: "C";    type: "cmd";        func: "clr";             color: "" }
                    ListElement { name: "Del";  type: "cmd";        func: "del";             color: "#c42b1c" }
                    ListElement { name: "1/x";  type: "function";    func: "1/(%1)";          color: "" }
                    ListElement { name: "x^2";  type: "function";    func: "Math.pow(%1, 2)"; color: "" }
                    ListElement { name: "2√";   type: "function";    func: "Math.sqrt(%1)";   color: "" }
                    ListElement { name: "÷";    type: "operator";   func: "/";               color: "" }
                    ListElement { name: "7";    type: "value";      func: "7";               color: "#31313d" }
                    ListElement { name: "8";    type: "value";      func: "8";               color: "#31313d" }
                    ListElement { name: "9";    type: "value";      func: "9";               color: "#31313d" }
                    ListElement { name: "x";    type: "operator";   func: "*";               color: "" }
                    ListElement { name: "4";    type: "value";      func: "4";               color: "#31313d" }
                    ListElement { name: "5";    type: "value";      func: "5";               color: "#31313d" }
                    ListElement { name: "6";    type: "value";      func: "6";               color: "#31313d" }
                    ListElement { name: "-";    type: "operator";   func: "-";               color: "" }
                    ListElement { name: "1";    type: "value";      func: "1";               color: "#31313d" }
                    ListElement { name: "2";    type: "value";      func: "2";               color: "#31313d" }
                    ListElement { name: "3";    type: "value";      func: "3";               color: "#31313d" }
                    ListElement { name: "+";    type: "operator";   func: "+";               color: "" }
                    ListElement { name: "+/-";  type: "cmd";        func: "cnvrt";               color: "#31313d" }
                    ListElement { name: "0";    type: "value";      func: "0";               color: "#31313d" }
                    ListElement { name: ".";    type: "value";      func: ".";               color: "#31313d" }
                    ListElement { name: "=";    type: "cmd";        func: "equal";           color: "#afadcc" }
                }
            }
        }
    }
}
