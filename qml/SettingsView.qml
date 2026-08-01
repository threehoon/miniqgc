import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// App settings placeholder — ground-station settings (≠ vehicle parameters / Fact).
Rectangle {
    id: root
    color: "#1f1a24"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 10

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Settings")
            color: "#f0e8f5"
            font.pixelSize: 32
            font.bold: true
        }
        Label {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Application settings shell (M1)\nVehicle parameters will use Facts (P1), not this page alone.")
            color: "#a08bad"
            font.pixelSize: 14
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
