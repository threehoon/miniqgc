import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Fly stage placeholder — later: vehicle status, map, guided actions (P4: bind Facts/Vehicle only).
Rectangle {
    id: root
    color: "#1a1f2e"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 10

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Fly")
            color: "#e8eefc"
            font.pixelSize: 32
            font.bold: true
        }
        Label {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("In-flight monitoring shell (M1)\nTelemetry & vehicle binding come with M4–M5.")
            color: "#8b9bb8"
            font.pixelSize: 14
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
