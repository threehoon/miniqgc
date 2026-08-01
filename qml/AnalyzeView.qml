import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Analyze placeholder — QGC often loads this via tool drawer; Mini uses a top-level tab for simplicity.
Rectangle {
    id: root
    color: "#241f1a"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 10

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Analyze")
            color: "#f5efe8"
            font.pixelSize: 32
            font.bold: true
        }
        Label {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Logs / MAVLink inspector shell (M1)\nNot implemented yet.")
            color: "#ad9f8b"
            font.pixelSize: 14
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
