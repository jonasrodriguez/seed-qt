import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: mainWindow
    visible: true
    title: qsTr("QT Seed")

    width: 1280
    height: 720

    Dashboard {
        anchors.fill: parent
    }
}
