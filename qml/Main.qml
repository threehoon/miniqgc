import QtQuick
import QtQuick.Controls

// M0 shell only — no MAVLink / sockets (P4).
ApplicationWindow {
    id: root
    width: 960
    height: 600
    visible: true
    title: qsTr("MiniQGC")

    Rectangle {
        anchors.fill: parent
        color: "#1e1e1e"

        Column {
            anchors.centerIn: parent
            spacing: 12

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("MiniQGC")
                color: "#f0f0f0"
                font.pixelSize: 28
                font.bold: true
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("M0 shell — composition root ready")
                color: "#a0a0a0"
                font.pixelSize: 14
            }
        }
    }
}
