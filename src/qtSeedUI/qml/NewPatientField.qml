import QtQuick 2.0

Item {
    property string fieldName: "Field"
    property alias fieldValue : valueText
    property alias valueArea : valueArea

    id: fieldArea
    width: parent.width * 0.9
    height: newUserTitleArea.height * 0.8
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.topMargin: height * 0.3

    Item {
        id: labelArea
        width: parent.width / 3
        height: parent.height
        anchors.left: parent.left

        Text {
            id: labelText
            width: parent.width
            height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: width * 0.1
            verticalAlignment: Text.AlignVCenter
            text: fieldName
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: valueArea
        width: parent.width - labelArea.width
        height: parent.height
        anchors.right: parent.right
        color: "#ffffff"

        TextInput {
            id: valueText
            width: parent.width
            height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: width * 0.08
            verticalAlignment: Text.AlignVCenter
            maximumLength: 31
            font.pixelSize: 12
            text: qsTr("")
        }
    }
}
