import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    anchors.fill: parent
    radius: 5
    opacity: 0.7

    BusyIndicator {
       id: busyIndication
       anchors.centerIn: parent
    }
}
