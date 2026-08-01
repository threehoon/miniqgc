import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// M1 shell: top-level view switching (P4 — UI only, no MAVLink/sockets).
// Mental model aligned with QGC MainWindow: Fly/Plan as primary stages;
// Analyze/Settings as secondary places (simplified — all peer tabs for now).
ApplicationWindow {
    id: root
    width: 1024
    height: 640
    visible: true
    title: qsTr("MiniQGC — %1").arg(viewModel.currentTitle)

    // View indices — keep in sync with StackLayout order and nav buttons.
    readonly property int viewFly: 0
    readonly property int viewPlan: 1
    readonly property int viewAnalyze: 2
    readonly property int viewSettings: 3

    QtObject {
        id: viewModel
        property int currentIndex: root.viewFly
        readonly property var titles: [
            qsTr("Fly"),
            qsTr("Plan"),
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
        id: topBar
        height: 48

        background: Rectangle {
            color: "#2b2b2b"
        }

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

            Item {
                Layout.fillWidth: true
            }

            ButtonGroup {
                id: navGroup
            }

            Repeater {
                model: [
                    { title: qsTr("Fly"), index: root.viewFly },
                    { title: qsTr("Plan"), index: root.viewPlan },
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
        background: Rectangle {
            color: "#252525"
        }

        Label {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 12
            text: qsTr("View: %1  ·  No vehicle (expected until M4)").arg(viewModel.currentTitle)
            color: "#9a9a9a"
            font.pixelSize: 12
        }
    }

    StackLayout {
        id: stack
        anchors.fill: parent
        currentIndex: viewModel.currentIndex

        FlyView {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        PlanView {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        AnalyzeView {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        SettingsView {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
