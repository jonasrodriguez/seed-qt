import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Shapes 1.0
import "elements"

Item {
    id: patientsArea
    height: parent.height
    width: parent.width

    //Title
    Item {
        id: patientTitleArea

        width: parent.width * 0.8
        height: parent.height * 0.1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: height
        anchors.leftMargin: height

        Text {
            id: patientTitleText
            text: qsTr("Patient List")
            font.pixelSize: 30
            font.family: "PT Mono"
            color: "white"
        }        
    }

    //Patient List
    Item {
        id: patientListArea
        width: parent.width * 0.8
        height: parent.height * 0.7
        anchors.top: patientTitleArea.bottom
        anchors.left: patientTitleArea.left

        ListView {
            anchors.fill: parent
            anchors.topMargin: 4
            spacing: 1
            clip: true

            model: patientList
            delegate: PatientListDelegate {}

            flickableDirection: Flickable.VerticalFlick
            boundsBehavior: Flickable.OvershootBounds
            ScrollBar.vertical: ScrollBar {
                anchors.right: parent.right
            }
        }
    }

    //Add user button
    Rectangle {
        id: addUserButton
        width: refreshButton.width
        height: width
        color: "#f47023"
        radius: width * 0.5
        anchors.left: refreshButton.left
        anchors.bottom: refreshButton.top
        anchors.bottomMargin: height / 5

        AddNewPatientButton {}

        MouseArea {
            anchors.fill: parent
            onClicked: {
                //Set inactive to reset the dialog in case it was open previously...
                patientDialogLoad.active = false
                patientDialogLoad.active = true
                patientDialogLoad.item.open()
             }
         }
    }

    //Refresh Button
    Item {
        id: refreshButton
        width: patientTitleArea.height * 0.5
        height: width
        anchors.left: patientListArea.right
        anchors.bottom: patientListArea.bottom
        anchors.leftMargin: width / 4
        Image {
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: "images/RefreshIcon.png"
         }
        MouseArea {
            anchors.fill: parent
            onClicked: patientList.refreshPatientList()
        }
    }

    //Patient Dialog Loader
    Loader {
        id: patientDialogLoad
        source: "PatientDialog.qml"
        active: false
    }
}
