import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Shapes 1.0

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
            delegate: delegate

            flickableDirection: Flickable.VerticalFlick
            boundsBehavior: Flickable.OvershootBounds
            ScrollBar.vertical: ScrollBar {
                anchors.right: parent.right
            }
        }

        Component {
            id: delegate
            PatientDelegate {
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

        Shape {
            id: canvas
            height: parent.height * 0.8
            width: height
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            ShapePath {
                strokeColor: "white"
                strokeWidth: 3
                startX: canvas.width * 0.2
                startY: (canvas.height / 2)
                PathLine {x:canvas.width / 2    ; y:canvas.height / 2}
                PathLine {x:canvas.width / 2    ; y:canvas.height * 0.2}
                PathLine {x:canvas.width / 2    ; y:canvas.height * 0.8}
                PathLine {x:canvas.width / 2    ; y:canvas.height / 2}
                PathLine {x:canvas.width * 0.8  ; y:canvas.height / 2}
            }
        }
//        Rectangle {
//            height: parent.height * 0.7
//            width: height
//            anchors.left: parent.left
//            anchors.centerIn: parent
//            radius: 5
//            color: "white"

//        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                //Set inactive to reset the dialog in case it was open previously...
                patientDialogLoad.active = false
                patientDialogLoad.active = true
                patientDialogLoad.item.open()
             }
         }

         Component {
             id: dlgComp
             NewPatient {}
         }

         Loader {
             id: patientDialogLoad
             sourceComponent: dlgComp
             active: false
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
            source: "res/RefreshIcon.png"
         }
        MouseArea {
            anchors.fill: parent
            onClicked: patientList.refreshPatientList()
        }
    }
}
