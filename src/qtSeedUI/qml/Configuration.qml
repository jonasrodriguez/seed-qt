import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    anchors.fill: parent

    property variant ipList: dashboardLogic.ip.split('.')
    Component.onCompleted: {
        ipRepeat.itemAt(0).children[0].text = ipList[0]
        ipRepeat.itemAt(1).children[0].text = ipList[1]
        ipRepeat.itemAt(2).children[0].text = ipList[2]
        ipRepeat.itemAt(3).children[0].text = ipList[3]
    }

    Item {
        id: ipArea
        width: parent.width / 3
        height: width * 0.15
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -parent.height / 5

        Item {
            id: ipLabel
            height: parent.height * 0.8
            width: parent.width / 5
            anchors.top: parent.top
            anchors.left: parent.left
            Text {
                text: qsTr("IP")
                font.family: "PT Mono"
                font.pixelSize: 16
                color: "#96cb2d"
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        Item {
            id: ipRows
            height: ipLabel.height
            width: (ipArea.width - ipLabel.width) * 0.95
            anchors.top: parent.top
            anchors.left: ipLabel.right
            anchors.leftMargin: height * 0.40
            RowLayout {
                anchors.fill: parent
                spacing: 5
                Repeater {
                    id: ipRepeat
                    model: 4
                    Rectangle {
                        Layout.fillHeight: true
                        Layout.preferredWidth: ipRows.width / 4
                        color: "#282828"
                        TextInput{
                            font.family: "PT Mono"
                            font.pixelSize: 16
                            color: "#cfc56a"
                            maximumLength: 3
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                        }
                    }
                }
            }
        }
    }

    Item {
        id: portArea
        height: ipArea.height
        width: ipArea.width
        anchors.left: ipArea.left
        anchors.top: ipArea.bottom

        Item {
            id: portLabel
            height: ipLabel.height
            width: ipLabel.width
            anchors.top: parent.top
            anchors.left: parent.left
            Text {
                text: qsTr("Port")
                font.family: "PT Mono"
                font.pixelSize: 16
                color: "#96cb2d"
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        Rectangle {
            height: portLabel.height
            width: portLabel.width * 1.3
            anchors.top: parent.top
            anchors.left: portLabel.right
            anchors.leftMargin: height * 0.40
            radius: 5
            color: "#282828"
            TextInput{
                id: portValue
                font.family: "PT Mono"
                font.pixelSize: 16
                color: "#cfc56a"
                maximumLength: 5
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: dashboardLogic.port
            }
        }
    }

    Rectangle {

        height: ipLabel.height
        width: ipLabel.width
        anchors.top: portArea.bottom
        anchors.topMargin: height / 2
        anchors.horizontalCenter: portArea.horizontalCenter
        radius: 5
        color: "#282828"
        border.color: "white"
        border.width: (saveMouse.containsMouse) ? 2 : 1

        Text{
            text: "Save"
            font.pixelSize: 16
            font.family: "PT Mono"
            color: "white"
            font.bold: (saveMouse.containsMouse) ? true : false
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        MouseArea {
            id: saveMouse
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                dashboardLogic.buttonSaveConf(ipRepeat.itemAt(0).children[0].text + "." + ipRepeat.itemAt(1).children[0].text + "." +
                                              ipRepeat.itemAt(2).children[0].text + "." + ipRepeat.itemAt(3).children[0].text)
            }
        }
    }
}
