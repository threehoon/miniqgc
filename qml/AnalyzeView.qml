import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// M3: thin MAVLink inspector shell — same parser as Link page (no second parse path).
Rectangle {
    id: root
    color: "#241f1a"

    readonly property var parser: typeof mavlinkParser !== "undefined" ? mavlinkParser : null

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        Label {
            text: qsTr("Analyze")
            color: "#f5efe8"
            font.pixelSize: 26
            font.bold: true
        }

        Label {
            text: qsTr("Protocol view of the shared MavlinkParser (wired from Application). Start the Link first.")
            color: "#ad9f8b"
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        GridLayout {
            columns: 2
            columnSpacing: 16
            rowSpacing: 6
            Layout.fillWidth: true

            Label { text: qsTr("Messages parsed"); color: "#ad9f8b" }
            Label {
                text: root.parser ? String(root.parser.messagesParsed) : "0"
                color: "#f5efe8"
            }

            Label { text: qsTr("HEARTBEATs"); color: "#ad9f8b" }
            Label {
                text: root.parser ? String(root.parser.heartbeatsParsed) : "0"
                color: root.parser && root.parser.heartbeatsParsed > 0 ? "#8dcea0" : "#f5efe8"
            }

            Label { text: qsTr("Last system"); color: "#ad9f8b" }
            Label {
                text: {
                    if (!root.parser || !root.parser.hasHeartbeat)
                        return qsTr("(no heartbeat yet)")
                    return "sysid=%1  compid=%2  type=%3  autopilot=%4  base_mode=0x%5  custom_mode=%6  status=%7"
                        .arg(root.parser.lastSysId)
                        .arg(root.parser.lastCompId)
                        .arg(root.parser.lastType)
                        .arg(root.parser.lastAutopilot)
                        .arg(root.parser.lastBaseMode.toString(16))
                        .arg(root.parser.lastCustomMode)
                        .arg(root.parser.lastSystemStatus)
                }
                color: "#f5efe8"
                font.family: "Menlo"
                font.pixelSize: 12
                Layout.fillWidth: true
                wrapMode: Text.WordWrap
            }
        }

        Label {
            text: qsTr("HEARTBEAT log")
            color: "#d8cfc4"
            font.bold: true
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "#1a1612"
            border.color: "#3a3228"
            radius: 4

            ListView {
                id: logView
                anchors.fill: parent
                anchors.margins: 8
                clip: true
                model: root.parser ? root.parser.logLines : []
                delegate: Label {
                    width: logView.width
                    text: modelData
                    color: "#c8d8b8"
                    font.family: "Menlo"
                    font.pixelSize: 12
                    wrapMode: Text.WrapAnywhere
                }
                onCountChanged: if (count > 0) positionViewAtEnd()
            }
        }
    }
}
