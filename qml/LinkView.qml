import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// M2: UDP link panel — binds context property `udpLink` (created in Application).
Rectangle {
    id: root
    color: "#151a22"

    // udpLink is injected from C++ (Application). Guard for design-time.
    readonly property var link: typeof udpLink !== "undefined" ? udpLink : null

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        Label {
            text: qsTr("Link (UDP)")
            color: "#e8eefc"
            font.pixelSize: 26
            font.bold: true
        }

        Label {
            text: qsTr("Listen for raw UDP datagrams (e.g. MAVLink on 14550). Parsing is M3.")
            color: "#8b9bb8"
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        RowLayout {
            spacing: 12
            Layout.fillWidth: true

            Label {
                text: qsTr("Local port")
                color: "#c0c8d8"
            }
            SpinBox {
                id: portBox
                from: 1
                to: 65535
                value: root.link ? root.link.localPort : 14550
                editable: true
                enabled: root.link && !root.link.running
                onValueModified: {
                    if (root.link)
                        root.link.localPort = value
                }
            }

            Button {
                text: root.link && root.link.running ? qsTr("Stop") : qsTr("Start")
                enabled: root.link !== null
                onClicked: {
                    if (!root.link)
                        return
                    if (root.link.running)
                        root.link.stop()
                    else if (!root.link.start())
                        console.warn("UDP start failed:", root.link.lastError)
                }
            }

            Button {
                text: qsTr("Clear log")
                enabled: root.link !== null
                onClicked: if (root.link) root.link.clearLog()
            }

            Item { Layout.fillWidth: true }
        }

        GridLayout {
            columns: 2
            columnSpacing: 16
            rowSpacing: 6
            Layout.fillWidth: true

            Label { text: qsTr("Status"); color: "#8b9bb8" }
            Label {
                text: root.link ? root.link.statusText : qsTr("n/a")
                color: root.link && root.link.running ? "#6dcea0" : "#e0a060"
                font.bold: true
            }

            Label { text: qsTr("Packets"); color: "#8b9bb8" }
            Label {
                text: root.link ? String(root.link.packetsReceived) : "0"
                color: "#e8eefc"
            }

            Label { text: qsTr("Bytes"); color: "#8b9bb8" }
            Label {
                text: root.link ? String(root.link.bytesReceived) : "0"
                color: "#e8eefc"
            }

            Label { text: qsTr("Last error"); color: "#8b9bb8" }
            Label {
                text: root.link && root.link.lastError.length ? root.link.lastError : qsTr("(none)")
                color: root.link && root.link.lastError.length ? "#e07070" : "#6a7388"
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
            }
        }

        Label {
            text: qsTr("Receive log")
            color: "#c0c8d8"
            font.bold: true
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#0d1118"
            border.color: "#2a3344"
            radius: 4

            ListView {
                id: logView
                anchors.fill: parent
                anchors.margins: 8
                clip: true
                model: root.link ? root.link.logLines : []
                delegate: Label {
                    width: logView.width
                    text: modelData
                    color: "#b8c4d8"
                    font.family: "Menlo"
                    font.pixelSize: 12
                    wrapMode: Text.WrapAnywhere
                }

                onCountChanged: {
                    if (count > 0)
                        positionViewAtEnd()
                }
            }
        }

        Label {
            text: qsTr("Tip: echo hello | nc -u -w1 127.0.0.1 14550")
            color: "#6a7388"
            font.pixelSize: 12
            font.family: "Menlo"
        }
    }
}
