import QtQuick 2.0
import QtQuick.Dialogs 1.2

Dialog {
    title: "Add New Patient"
    modality: Qt.WindowModal
    height: 550
    width: 400
    standardButtons: StandardButton.Cancel | StandardButton.Save

    onAccepted: {
        newPatientDlg.saveNewPatient(nameField.fieldValue.text, surnameField.fieldValue.text, yearValue.text + monthValue.text + dayValue.text,
                                     emailField.fieldValue.text, coorField.fieldValue.text, streetField.fieldValue.text, cityField.fieldValue.text, zipField.fieldValue.text);
        close();
    }

    property real fieldHeight: newUserTitleArea.height * 0.8
    property real fieldWidth:  dialogArea.width * 0.9

    Item {
        id: dialogArea
        anchors.fill: parent

        //Title
        Item {
            id: newUserTitleArea
            width: parent.width * 0.9
            height: parent.width * 0.1
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                id: newUserTitle
                text: qsTr("Add New Patient")
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 20
                font.family: "PT Mono"
            }

            Rectangle{
                width: parent.width
                height: 1
                border.color: "black"
                border.width: 1
                anchors.bottom: parent.bottom
                color: "transparent"
            }
        }

        //Name
        NewPatientField {
            id: nameField
            fieldName: "Patient Name"
            anchors.top: newUserTitleArea.bottom
            anchors.topMargin: height * 0.8
            KeyNavigation.tab: surnameField.fieldValue
        }

        //Surname
        NewPatientField {
            id: surnameField
            fieldName: "Patient Surname"
            anchors.top: nameField.bottom
            KeyNavigation.tab: yearValue
        }

        //Date of Birth
        NewPatientField {
            id: dobField
            fieldName: "Date of Birth"
            anchors.top: surnameField.bottom
            valueArea.color: "transparent"

            Item {
                id: dobTextArea
                width: dobField.valueArea.width
                height: dobField.valueArea.height
                anchors.right: dobField.valueArea.right
                //Year
                Rectangle {
                    id: yearTextArea
                    width: parent.width * 0.4
                    height: parent.height
                    anchors.left: parent.left
                    color: "#ffffff"
                    TextInput {
                        id: yearValue
                        width: parent.width
                        height: parent.height
                        anchors.left: parent.left
                        anchors.leftMargin: width * 0.08
                        verticalAlignment: Text.AlignVCenter
                        maximumLength: 4
                        font.pixelSize: 12
                        KeyNavigation.tab: monthValue
                        text: qsTr("")
                    }
                }
                //Month
                Rectangle {
                    id: monthTextArea
                    width: parent.width / 4
                    height: parent.height
                    anchors.left: yearTextArea.right
                    anchors.leftMargin: (parent.width - yearTextArea.width - (dayTextArea.width * 2)) / 2
                    color: "#ffffff"
                    TextInput {
                        id: monthValue
                        width: parent.width
                        height: parent.height
                        anchors.left: parent.left
                        anchors.leftMargin: width * 0.08
                        verticalAlignment: Text.AlignVCenter
                        maximumLength: 2
                        font.pixelSize: 12
                        KeyNavigation.tab: dayValue
                        text: qsTr("")
                    }
                }
                //Day
                Rectangle {
                    id: dayTextArea
                    width: parent.width / 4
                    height: parent.height
                    anchors.right: parent.right
                    color: "#ffffff"
                    TextInput {
                        id: dayValue
                        width: parent.width
                        height: parent.height
                        anchors.left: parent.left
                        anchors.leftMargin: width * 0.08
                        verticalAlignment: Text.AlignVCenter
                        maximumLength: 2
                        font.pixelSize: 12
                        KeyNavigation.tab: emailField.fieldValue
                        text: qsTr("")
                    }
                }
            }
        }

        //Email
        NewPatientField {
            id: emailField
            fieldName: "Patient Email"
            anchors.top: dobField.bottom
            KeyNavigation.tab: coorField.fieldValue
        }

        //Address Title
        Item {
            id: addressTitleArea
            width: newUserTitleArea.width
            height: newUserTitleArea.height * 0.9
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: emailField.bottom
            anchors.topMargin: height * 0.5

            Text {
                text: qsTr("Patient Address")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 16
                font.family: "PT Mono"
            }

            Rectangle{
                width: parent.width
                height: 1
                border.color: "black"
                border.width: 1
                anchors.bottom: parent.bottom
                color: "transparent"
            }
        }

        //Coordinates
        NewPatientField {
            id: coorField
            fieldName: "Coordinates"
            anchors.top: addressTitleArea.bottom
            KeyNavigation.tab: streetField.fieldValue
            anchors.topMargin: height * 0.8
        }

        //Street
        NewPatientField {
            id: streetField
            fieldName: "Street"
            anchors.top: coorField.bottom
            KeyNavigation.tab: cityField.fieldValue
        }

        //City
        NewPatientField {
            id: cityField
            fieldName: "City"
            anchors.top: streetField.bottom
            KeyNavigation.tab: zipField.fieldValue
        }

        //Zip
        NewPatientField {
            id: zipField
            fieldName: "Zip Code"
            anchors.top: cityField.bottom
        }
    }
}
