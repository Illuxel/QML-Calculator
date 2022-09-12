import QtQuick 2.15
import QtQuick.Shapes 1.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3

import "components" as CalculatorComponents
import Calculator.History 1.0

ApplicationWindow {
    id: window
    visible: true

    title: "Calculator QML"

    width: 335
    height: 505

    minimumWidth: 335
    minimumHeight: 505

    maximumWidth: 335
    maximumHeight: 505

    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint

    // windows
    property int bw: 1

    color: "transparent"

    background: Rectangle {
        id: bgColor
        color: "#1f1f27"
        radius: 12.5
        border.color: "grey"
        border.width: bw
    }

    // History.onCurrentItemChanged: {}

    // window menu layout
    header: ToolBar {
        id: windowToolBar
        height: 42
        width: window.width
        anchors.margins: 0
        // style
        background: Rectangle {
            color: "transparent"
        }
        Item {
            id: windowToolBarItem
            anchors.fill: parent
            clip: true
            // on move window handler
            DragHandler {
                id: moveHandler
                grabPermissions: TapHandler.TakeOverForbidden
                onActiveChanged: {
                    if (active){
                        window.startSystemMove();
                    }
                }
            }
            // window menu layout
            RowLayout {
                anchors.fill: parent
                spacing: 0
                Image {
                    source: "qrc:/app/assets/images/calculator.png"
                    sourceSize.width: 20
                    sourceSize.height: 20
                    Layout.leftMargin: 5
                }
                Text {
                    text: window.title
                    font.pixelSize: 14
                    font.family: "Segoe"
                    color: "white"
                    Layout.leftMargin: 5
                }

                Item { Layout.fillWidth: true }

                CalculatorComponents.StyledWindowButtons {
                    iconSource: "qrc:/app/assets/images/subtract.ico"
                    hoverColor: bgColor.color
                    Layout.minimumWidth: 42
                    onClicked: window.showMinimized();
                }
                CalculatorComponents.StyledWindowButtons {
                    iconSource: "qrc:/app/assets/images/close.ico"
                    hoverColor: hovered ? "red" : "#1f1f27"
                    Layout.minimumWidth: 42
                    onClicked: window.close()
                }
            }
        }
    }
    //
    Page {
        id: mainPage
        anchors.fill: parent
        background: Rectangle {
            color: "transparent"
        }
        // calculator tool bar layout
        header: ToolBar {
            id: calcToolBar
            height: 46
            width: window.width
            RowLayout {
                anchors.fill: parent
                spacing: 0
                // drawer button
                CalculatorComponents.StyledDrawerButton {
                    id: drawerButton

                    Layout.leftMargin: 6
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft

                    iconSource: "qrc:/app/assets/images/menu.ico"
                    onClicked: {
                        if (drawerMainList.opened)
                            drawerMainList.close()
                        else
                            drawerMainList.open()
                    }
                }
                // Status of opened tab
                Label {
                    id: calcType

                    Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
                    Layout.minimumWidth: 150

                    text: "Standart"
                    color: "#e5e5e5"
                    font.bold: true
                    font.pixelSize: 20
                }
                // History
                CalculatorComponents.StyledDrawerButton {
                    id: historyButton

                    Layout.rightMargin: 6
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignRight

                    iconSource: "qrc:/app/assets/images/history.ico"
                    onClicked: {
                        historyListView.model = History.list;
                        drawerHistory.open();
                    }
                }
            }
            background: Rectangle {
                color: "transparent"
            }
        }

        StackView {
            id: stackView
            anchors.fill: parent
            anchors.margins: bw
            clip: true
            initialItem: "qrc:/app/qml/pages/Standart.qml"
        }

        Drawer {
            id: drawerMainList

            width: 250
            height: parent.height - windowToolBar.height

            y: parent.y - windowToolBar.y

            edge: Qt.LeftEdge

            dim: true
            modal: true
            interactive: false

            background: Rectangle {
                radius: 12.5
                color: "#2e2e2e"
                border.color: "grey"
                border.width: bw
                opacity: 0.967
                Rectangle {
                    width: parent.radius
                    anchors.rightMargin: drawerMainList.width - parent.radius
                    color: parent.color
                }
            }
            ListView {
                id: drawerList
                anchors.centerIn: parent
                width: drawerMainList.width * 0.90
                height: 250
                clip: true
                spacing: 5

                delegate: CalculatorComponents.StyledToolButton {
                    iconSource: icosource
                    iconH: 32
                    iconW: 32
                    width: drawerList.width
                    height: 48
                    textButton: name
                    onClicked: {
                        drawerMainList.close();
                        stackView.pop();
                        stackView.push(page)
                        calcType.text = name;
                    }
                }
                model: ListModel {
                    ListElement { name: "Standart"; icosource: "qrc:/app/assets/images/standart.ico";   page: "qrc:/app/qml/pages/Standart.qml" }
                    ListElement { name: "Angle";    icosource: "qrc:/app/assets/images/angle.ico";      page: "qrc:/app/qml/pages/Angle.qml" }
                    ListElement { name: "Data";     icosource: "qrc:/app/assets/images/data.ico";       page: "qrc:/app/qml/pages/DataUnits.qml" }
                }
            }
        }
        Drawer {
            id: drawerHistory
            width: window.width
            height: 310 - bw
            y: parent.y + bw

            modal: true
            interactive: true

            edge: Qt.BottomEdge

            background: Rectangle {
                radius: 12.5
                color: "#2e2e2e"
                border.color: "grey"
                border.width: bw
            }

            ListView {
                id: historyListView
                anchors.centerIn: parent
                width: 250
                height: parent.height - windowToolBar.height

                clip: true
                spacing: 5

                delegate: CalculatorComponents.StyledToolButton {
                    width: parent.width
                    height: 48
                    textButton: modelData
                    onClicked:
                        History.currentItem = modelData;
                }
            }
        }
    }
}
