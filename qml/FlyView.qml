import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// M4: show active vehicle (nullable). P2: always guard before use.
Rectangle {
    id: root
    color: "#1a1f2e"

    readonly property var manager: typeof vehicleManager !== "undefined" ? vehicleManager : null
    readonly property var vehicle: root.manager ? root.manager.activeVehicle : null

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 16

        Label {
            text: qsTr("Fly")
            color: "#e8eefc"
            font.pixelSize: 28
            font.bold: true
        }

        Label {
            text: qsTr("Vehicle comes from HEARTBEAT via VehicleManager (not from Link start alone).")
            color: "#8b9bb8"
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: card.implicitHeight + 24
            radius: 8
            color: root.vehicle ? "#1e3d32" : "#2a2430"
            border.color: root.vehicle ? "#3d8f6a" : "#5a4058"

            ColumnLayout {
                id: card
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.margins: 16
                spacing: 8

                Label {
                    text: root.vehicle ? qsTr("Vehicle online") : qsTr("No vehicle")
                    color: root.vehicle ? "#6dcea0" : "#e0a0c0"
                    font.pixelSize: 20
                    font.bold: true
                }

                Label {
                    visible: root.vehicle === null
                    text: qsTr("Legal state (P2). Start Link and wait for HEARTBEAT, or run tools/send_heartbeat.py.")
                    color: "#ad9f8b"
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                }

                // P2: every field reads only when vehicle is non-null.
                GridLayout {
                    visible: root.vehicle !== null
                    columns: 2
                    columnSpacing: 16
                    rowSpacing: 6
                    Layout.fillWidth: true

                    Label { text: qsTr("sysId"); color: "#8b9bb8" }
                    Label {
                        text: root.vehicle ? String(root.vehicle.sysId) : ""
                        color: "#e8eefc"
                        font.family: "Menlo"
                    }

                    Label { text: qsTr("compId"); color: "#8b9bb8" }
                    Label {
                        text: root.vehicle ? String(root.vehicle.compId) : ""
                        color: "#e8eefc"
                        font.family: "Menlo"
                    }

                    Label { text: qsTr("type"); color: "#8b9bb8" }
                    Label {
                        text: root.vehicle ? String(root.vehicle.vehicleType) : ""
                        color: "#e8eefc"
                        font.family: "Menlo"
                    }

                    Label { text: qsTr("autopilot"); color: "#8b9bb8" }
                    Label {
                        text: root.vehicle ? String(root.vehicle.autopilotType) : ""
                        color: "#e8eefc"
                        font.family: "Menlo"
                    }

                    Label { text: qsTr("systemStatus"); color: "#8b9bb8" }
                    Label {
                        text: root.vehicle ? String(root.vehicle.systemStatus) : ""
                        color: "#e8eefc"
                        font.family: "Menlo"
                    }

                    Label { text: qsTr("summary"); color: "#8b9bb8" }
                    Label {
                        text: root.vehicle ? root.vehicle.summaryText : ""
                        color: "#9dcea8"
                        font.family: "Menlo"
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                    }
                }
            }
        }

        Label {
            text: qsTr("M4 policy: first HEARTBEAT sysid is tracked; other sysids ignored; 5s silence or Link Stop clears vehicle.")
            color: "#6a7388"
            font.pixelSize: 12
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Item { Layout.fillHeight: true }
    }
}
