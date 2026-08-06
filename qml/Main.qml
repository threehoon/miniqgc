import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Shell + Link page (M1/M2). P4: UI binds services from Application, no sockets here.
ApplicationWindow {
    id: root
    width: 1100
    height: 700
    visible: true
    title: qsTr("MiniQGC — %1").arg(viewModel.currentTitle)

    readonly property int viewFly: 0
    readonly property int viewPlan: 1
    readonly property int viewLink: 2
    readonly property int viewAnalyze: 3
    readonly property int viewSettings: 4

    QtObject {
        id: viewModel
        property int currentIndex: root.viewLink
        readonly property var titles: [
            qsTr("Fly"),
            qsTr("Plan"),
            qsTr("Link"),
            qsTr("Analyze"),
            qsTr("Settings")
        ]
        readonly property string currentTitle: titles[currentIndex]

        function show(index) {
            if (index < 0 || index >= titles.length)
                return
            currentIndex = index
        }
    }

    header: ToolBar {
        height: 48
        background: Rectangle { color: "#2b2b2b" }

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 12
            anchors.rightMargin: 12
            spacing: 8

            Label {
                text: qsTr("MiniQGC")
                color: "#f0f0f0"
                font.bold: true
                font.pixelSize: 16
            }

            // Live link chip in the toolbar
            Rectangle {
                radius: 4
                color: (typeof udpLink !== "undefined" && udpLink.running) ? "#1e3d32" : "#3a3030"
                implicitHeight: 28
                implicitWidth: linkChipText.implicitWidth + 16
                visible: typeof udpLink !== "undefined"

                Label {
                    id: linkChipText
                    anchors.centerIn: parent
                    text: udpLink.running
                          ? qsTr("UDP :%1").arg(udpLink.localPort)
                          : qsTr("Link off")
                    color: udpLink.running ? "#6dcea0" : "#c09090"
                    font.pixelSize: 12
                }
            }

            // Vehicle chip (P2: null activeVehicle is normal)
            Rectangle {
                radius: 4
                color: (typeof vehicleManager !== "undefined" && vehicleManager.hasVehicle)
                       ? "#1e3d32" : "#3a3030"
                implicitHeight: 28
                implicitWidth: vehicleChipText.implicitWidth + 16
                visible: typeof vehicleManager !== "undefined"

                Label {
                    id: vehicleChipText
                    anchors.centerIn: parent
                    text: {
                        if (typeof vehicleManager === "undefined")
                            return ""
                        if (!vehicleManager.hasVehicle || !vehicleManager.activeVehicle)
                            return qsTr("No vehicle")
                        return qsTr("Vehicle sys=%1").arg(vehicleManager.activeVehicle.sysId)
                    }
                    color: (typeof vehicleManager !== "undefined" && vehicleManager.hasVehicle)
                           ? "#6dcea0" : "#c09090"
                    font.pixelSize: 12
                }
            }

            Item { Layout.fillWidth: true }

            ButtonGroup { id: navGroup }

            Repeater {
                model: [
                    { title: qsTr("Fly"), index: root.viewFly },
                    { title: qsTr("Plan"), index: root.viewPlan },
                    { title: qsTr("Link"), index: root.viewLink },
                    { title: qsTr("Analyze"), index: root.viewAnalyze },
                    { title: qsTr("Settings"), index: root.viewSettings }
                ]

                delegate: Button {
                    required property var modelData
                    text: modelData.title
                    checkable: true
                    checked: viewModel.currentIndex === modelData.index
                    ButtonGroup.group: navGroup
                    onClicked: viewModel.show(modelData.index)

                    background: Rectangle {
                        radius: 4
                        color: parent.checked ? "#3d7eff" : (parent.hovered ? "#404040" : "transparent")
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "#f0f0f0"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }
    }

    footer: ToolBar {
        height: 28
        background: Rectangle { color: "#252525" }

        Label {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 12
            text: {
                var linkPart = (typeof udpLink !== "undefined" && udpLink.running)
                    ? qsTr("UDP :%1 · %2 pkts").arg(udpLink.localPort).arg(udpLink.packetsReceived)
                    : qsTr("Link stopped")
                var vehiclePart = (typeof vehicleManager !== "undefined")
                    ? vehicleManager.statusText
                    : qsTr("No vehicle")
                return qsTr("View: %1  ·  %2  ·  %3")
                    .arg(viewModel.currentTitle)
                    .arg(linkPart)
                    .arg(vehiclePart)
            }
            color: "#9a9a9a"
            font.pixelSize: 12
        }
    }

    StackLayout {
        anchors.fill: parent
        currentIndex: viewModel.currentIndex

        FlyView { Layout.fillWidth: true; Layout.fillHeight: true }
        PlanView { Layout.fillWidth: true; Layout.fillHeight: true }
        LinkView { Layout.fillWidth: true; Layout.fillHeight: true }
        AnalyzeView { Layout.fillWidth: true; Layout.fillHeight: true }
        SettingsView { Layout.fillWidth: true; Layout.fillHeight: true }
    }
}
