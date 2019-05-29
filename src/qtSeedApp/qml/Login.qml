import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Rectangle{
    id: idLogin

    Item {
        id: idItemLogin
        width: mainArea.width / 3
        height: width / 2
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -parent.height / 5

        Component.onCompleted: idUsernameTextField.forceActiveFocus()

        ColumnLayout {
            id: idLoginColumn
            width: parent.width
            anchors.top: parent.top
            spacing: 3
            Keys.onPressed: if (event.key === Qt.Key_Return) { dashboardLogic.buttonLogin(idUsernameTextField.text, idPasswordTextField.text) }

            TextField {
                id: idUsernameTextField
                Layout.fillWidth: true
                placeholderText: "User Name"
                KeyNavigation.tab: idPasswordTextField
            }

            TextField {
                id: idPasswordTextField
                Layout.fillWidth: true
                placeholderText: "Password"
                echoMode: TextInput.Password
                KeyNavigation.tab: idBtnLogin
            }

            Button {
                id: idBtnLogin
                Layout.fillWidth: true
                text: "Login"
                KeyNavigation.tab: idUsernameTextField
                onClicked: dashboardLogic.buttonLogin(idUsernameTextField.text, idPasswordTextField.text);
            }
        }
    }

    Item {
        id: errorMsgArea
        height: width / 2
        width: idItemLogin.width
        anchors.top: idItemLogin.bottom
        anchors.horizontalCenter: idItemLogin.horizontalCenter
        Text {
            id: errorMsg
            text: dashboardLogic.loginError
            color: "red"
            font.family: "PT mono"
            font.pixelSize: 14
        }
    }
}
