import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    anchors.fill: parent

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
                anchors.centerIn: parent
            }
        }
        Rectangle {
            height: ipLabel.height
            width: (ipArea.width - ipLabel.width) * 0.95
            anchors.top: parent.top
            anchors.left: ipLabel.right
            anchors.leftMargin: height * 0.40
            color: "#282828"

            TextInput{
                id: ipValue

                text: dashboardLogic.ip
                font.family: "PT Mono"
                font.pixelSize: 16
                color: "#cfc56a"
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                anchors.leftMargin: parent.height / 3
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
                anchors.centerIn: parent
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

                text: dashboardLogic.port
                font.family: "PT Mono"
                font.pixelSize: 16
                color: "#cfc56a"
                maximumLength: 8
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                anchors.leftMargin: parent.height / 3
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
                dashboardLogic.buttonSaveConf(ipValue.text, portValue.text)
            }
        }
    }
}
