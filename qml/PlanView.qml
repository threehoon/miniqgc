import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Plan stage placeholder — later: mission items, upload/download.
Rectangle {
    id: root
    color: "#1a2420"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 10

        Label {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Plan")
            color: "#e8f5ef"
            font.pixelSize: 32
            font.bold: true
        }
        Label {
            Layout.alignment: Qt.AlignHCenter
            text: qsTr("Mission planning shell (M1)\nWaypoints & mission protocol come later.")
            color: "#8bada0"
            font.pixelSize: 14
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
