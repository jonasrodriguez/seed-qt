import QtQuick 2.0

Rectangle {
    id: delegateArea
    width: patientListArea.width * 0.99
    height: patientListArea.height / 7
    anchors.horizontalCenter: parent.horizontalCenter
    color: "#282828"
    border.width: 1

    MouseArea {
        anchors.fill: parent
        onPressAndHold: patientList.deletePatient(idArea.fieldValue);
    }

    Loader {
        id: idArea
        property string fieldName: "ID"
        property string fieldValue: model.id
        width: parent.width * 0.07
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: height / 3
        anchors.topMargin:  height / 3
        sourceComponent: delegateComponent
    }

    Loader {
        id: nameArea
        property string fieldName: "Patient Name"
        property string fieldValue: model.name
        width: parent.width * 0.3
        anchors.left: idArea.right
        anchors.top: idArea.top
        anchors.leftMargin: implicitHeight / 3
        sourceComponent: delegateComponent
    }

    Loader {
        id: surnameArea
        property string fieldName: "Patient Surname"
        property string fieldValue: model.surname
        anchors.left: nameArea.right;
        anchors.top: idArea.top
        anchors.leftMargin: implicitHeight / 3
        sourceComponent: delegateComponent
    }

    Loader {
        id: doblArea
        property string fieldName: "Date of Birth"
        property string fieldValue: model.dob
        width: parent.width * 0.3
        anchors.left: nameArea.left;
        anchors.top: nameArea.bottom;
        anchors.topMargin: implicitHeight / 5
        sourceComponent: delegateComponent
    }

    Loader {
        id: emailArea
        property string fieldName: "Patient Email"
        property string fieldValue: model.email
        anchors.left: surnameArea.left;
        anchors.top: doblArea.top;
        sourceComponent: delegateComponent
    }

    Component {
        id: delegateComponent
        Item {
            width: delegateArea.width * 0.4
            height: delegateArea.height * 0.3

            Item {
                id: labelArea
                width: parent.width / 3
                height: parent.height

                Text {
                    id: labelText
                    anchors.verticalCenter: parent.verticalCenter
                    text: fieldName
                    font.family: "PT Mono"
                    font.bold: true
                    font.pixelSize: 12
                    color: "#96cb2d"
                }
            }
            Rectangle {
                id: valueArea
                width: parent.width - labelArea.width
                height: parent.height
                color: "transparent"
                anchors.left: labelArea.right
                Text{
                    id: valueText
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: height / 2
                    text: fieldValue
                    font.family: "PT Mono"
                    font.pixelSize: 12
                    color: "#cfc56a"
                }
            }
        }
    }
}
