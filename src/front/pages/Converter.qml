import QtQuick 2.15
import QtQuick.Shapes 1.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

import "../components" as CalculatorComponents
import Calculator.Converter 1.0

Page {
	id: page

	background: Rectangle {
        color: "transparent"
    }

	ColumnLayout {
		anchors.fill: parent
        spacing: 1
		CalculatorComponents.StyledTextInput {
			id: firstTypeInput

			Layout.fillWidth: true
			Layout.minimumHeight: 32
			Layout.margins: 10

			textSize: 30
		}
		ComboBox {
			id: firstTypeBox
            model: Converter.typeList
		}

        CalculatorComponents.StyledTextInput {
			id: secondTypeInput

			Layout.fillWidth: true
			Layout.minimumHeight: 32
			Layout.margins: 10

			textSize: 30
		}
		ComboBox {
			id: secondTypeBox
            model: Converter.typeList
		}

		Rectangle {
            id: gridInputStyle
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
            GridView {
                id: gridView
                anchors.fill: parent
                anchors.margins: 10

                cellHeight: gridView.height / 5
                cellWidth: gridView.width / 3

                interactive: false

                model: ListModel {
                    ListElement { ph: "";    color: "transparent" }
                    ListElement { ph: "CE";  type: "cmd";   func: "clr"; color: "#31313d" }
                    ListElement { ph: "Del"; type: "cmd";   func: "del"; color: "#c42b1c" }
                    ListElement { ph: "7";   type: "value"; func: "7";   color: "#31313d" }
                    ListElement { ph: "8";   type: "value"; func: "8";   color: "#31313d" }
                    ListElement { ph: "9";   type: "value"; func: "9";   color: "#31313d" }
                    ListElement { ph: "4";   type: "value"; func: "4";   color: "#31313d" }
                    ListElement { ph: "5";   type: "value"; func: "5";   color: "#31313d" }
                    ListElement { ph: "6";   type: "value"; func: "6";   color: "#31313d" }
                    ListElement { ph: "1";   type: "value"; func: "1";   color: "#31313d" }
                    ListElement { ph: "2";   type: "value"; func: "2";   color: "#31313d" }
                    ListElement { ph: "3";   type: "value"; func: "3";   color: "#31313d" }
                    ListElement { ph: "";    color: "transparent" }
                    ListElement { ph: "0";   type: "value"; func: "0";   color: "#31313d" }
                    ListElement { ph: ".";   type: "value"; func: ".";   color: "#31313d" }
                }
                delegate: CalculatorComponents.StyledToolButton {
                    height: 44
                    width: 96
                    iconH: 0
                    iconW: 0
                    fluentThikness: 0.89

                    enabled: (ph == "") ? false : true
                    visible: (ph == "") ? false : true

                    centered: false
                    itemSpacing: 0

                    textButton: ph
                    imageLeftMargin: 0

                    baseColor: (color === "")
                        ? CalculatorComponents.StyledToolButton.baseColor : color

                    onClicked: {
                        if (firstTypeInput.activeFocus)
                            firstTypeInput.textInput += ph;
                        if (secondTypeInput.activeFocus)
                            secondTypeInput.textInput += ph;
                    }
                }
            }
        }
	}
}
