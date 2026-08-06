import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// M2+M3: UDP link + MAVLink parse panel.
// Context properties: udpLink, mavlinkParser (created in Application).
Rectangle {
    id: root
    color: "#151a22"

    readonly property var link: typeof udpLink !== "undefined" ? udpLink : null
    readonly property var parser: typeof mavlinkParser !== "undefined" ? mavlinkParser : null

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 10

        Label {
            text: qsTr("Link (UDP) + MAVLink")
            color: "#e8eefc"
            font.pixelSize: 26
            font.bold: true
        }

        Label {
            text: qsTr("Start opens the byte pipe. HEARTBEAT lines mean the parser understood MAVLink (M3). Not a Vehicle yet (M4).")
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
                text: qsTr("Clear RX log")
                enabled: root.link !== null
                onClicked: if (root.link) root.link.clearLog()
            }

            Button {
                text: qsTr("Clear MAVLink log")
                enabled: root.parser !== null
                onClicked: if (root.parser) root.parser.clearLog()
            }

            Item { Layout.fillWidth: true }
        }

        GridLayout {
            columns: 4
            columnSpacing: 16
            rowSpacing: 6
            Layout.fillWidth: true

            Label { text: qsTr("Status"); color: "#8b9bb8" }
            Label {
                text: root.link ? root.link.statusText : qsTr("n/a")
                color: root.link && root.link.running ? "#6dcea0" : "#e0a060"
                font.bold: true
            }

            Label { text: qsTr("UDP packets"); color: "#8b9bb8" }
            Label {
                text: root.link ? String(root.link.packetsReceived) : "0"
                color: "#e8eefc"
            }

            Label { text: qsTr("MAVLink msgs"); color: "#8b9bb8" }
            Label {
                text: root.parser ? String(root.parser.messagesParsed) : "0"
                color: "#e8eefc"
            }

            Label { text: qsTr("HEARTBEATs"); color: "#8b9bb8" }
            Label {
                text: root.parser ? String(root.parser.heartbeatsParsed) : "0"
                color: root.parser && root.parser.heartbeatsParsed > 0 ? "#6dcea0" : "#e8eefc"
                font.bold: root.parser && root.parser.heartbeatsParsed > 0
            }

            Label { text: qsTr("Last HB"); color: "#8b9bb8" }
            Label {
                Layout.columnSpan: 3
                text: {
                    if (!root.parser || !root.parser.hasHeartbeat)
                        return qsTr("(none yet)")
                    return qsTr("sys=%1 comp=%2 type=%3 autopilot=%4 status=%5")
                        .arg(root.parser.lastSysId)
                        .arg(root.parser.lastCompId)
                        .arg(root.parser.lastType)
                        .arg(root.parser.lastAutopilot)
                        .arg(root.parser.lastSystemStatus)
                }
                color: root.parser && root.parser.hasHeartbeat ? "#6dcea0" : "#6a7388"
                font.family: "Menlo"
                font.pixelSize: 12
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 12

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 6

                Label {
                    text: qsTr("Raw RX (bytes)")
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
                        id: rxLogView
                        anchors.fill: parent
                        anchors.margins: 8
                        clip: true
                        model: root.link ? root.link.logLines : []
                        delegate: Label {
                            width: rxLogView.width
                            text: modelData
                            color: "#b8c4d8"
                            font.family: "Menlo"
                            font.pixelSize: 11
                            wrapMode: Text.WrapAnywhere
                        }
                        onCountChanged: if (count > 0) positionViewAtEnd()
                    }
                }
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 6

                Label {
                    text: qsTr("MAVLink HEARTBEAT")
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
                        id: hbLogView
                        anchors.fill: parent
                        anchors.margins: 8
                        clip: true
                        model: root.parser ? root.parser.logLines : []
                        delegate: Label {
                            width: hbLogView.width
                            text: modelData
                            color: "#9dcea8"
                            font.family: "Menlo"
                            font.pixelSize: 11
                            wrapMode: Text.WrapAnywhere
                        }
                        onCountChanged: if (count > 0) positionViewAtEnd()
                    }
                }
            }
        }

        Label {
            text: qsTr("Tip: SITL → UDP 14550, or tools/send_heartbeat.py 127.0.0.1 14550")
            color: "#6a7388"
            font.pixelSize: 12
            font.family: "Menlo"
        }
    }
}
