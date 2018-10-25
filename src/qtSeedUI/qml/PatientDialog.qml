import QtQuick 2.0
import QtQuick.Dialogs 1.2

import "elements"

Dialog {
    title: "Add New Patient"
    modality: Qt.WindowModal
    height: 550
    width: 400
    standardButtons: StandardButton.Cancel | StandardButton.Save

    property real fieldHeight: newUserTitleArea.height * 0.8
    property real fieldWidth:  dialogArea.width * 0.9

    onAccepted: {
        patientDialog.savePatientInfo(patientDialog.patient)
    }

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
        PatientDialogField {
            id: nameField
            fieldName: "Patient Name"
            fieldValue.text: patientDialog.patient.name
            fieldValue.onTextChanged: patientDialog.patient.name = fieldValue.text
            anchors.top: newUserTitleArea.bottom
            anchors.topMargin: height * 0.8
            KeyNavigation.tab: surnameField.fieldValue
        }

        //Surname
        PatientDialogField {
            id: surnameField
            fieldName: "Patient Surname"
            fieldValue.text: patientDialog.patient.surname
            fieldValue.onTextChanged: patientDialog.patient.surname = fieldValue.text
            anchors.top: nameField.bottom
            KeyNavigation.tab: yearValue
        }

        //Date of Birth
        PatientDialogField {
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
                        text: patientDialog.patient.dobYear
                        onTextChanged: patientDialog.patient.dobYear = text
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
                        text: patientDialog.patient.dobMonth
                        onTextChanged: patientDialog.patient.dobMonth = text
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
                        text: patientDialog.patient.dobDay
                        onTextChanged: patientDialog.patient.dobDay = text
                    }
                }
            }
        }

        //Email
        PatientDialogField {
            id: emailField
            fieldName: "Patient Email"
            fieldValue.text: patientDialog.patient.email
            fieldValue.onTextChanged: patientDialog.patient.email = fieldValue.text
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
        PatientDialogField {
            id: coorField
            fieldName: "Coordinates"
            fieldValue.text: patientDialog.patient.coor
            fieldValue.onTextChanged: patientDialog.patient.coor = fieldValue.text
            anchors.top: addressTitleArea.bottom
            KeyNavigation.tab: streetField.fieldValue
            anchors.topMargin: height * 0.8
        }

        //Street
        PatientDialogField {
            id: streetField
            fieldName: "Street"
            fieldValue.text: patientDialog.patient.street
            fieldValue.onTextChanged: patientDialog.patient.street = fieldValue.text
            anchors.top: coorField.bottom
            KeyNavigation.tab: cityField.fieldValue
        }

        //City
        PatientDialogField {
            id: cityField
            fieldName: "City"
            fieldValue.text: patientDialog.patient.city
            fieldValue.onTextChanged: patientDialog.patient.city = fieldValue.text
            anchors.top: streetField.bottom
            KeyNavigation.tab: zipField.fieldValue
        }

        //Zip
        PatientDialogField {
            id: zipField
            fieldName: "Zip Code"
            fieldValue.text: patientDialog.patient.zip
            fieldValue.onTextChanged: patientDialog.patient.zip = fieldValue.text
            anchors.top: cityField.bottom
        }
    }
}
