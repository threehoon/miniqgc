# ui（含 qml/）

| 字段 | 值 |
|------|-----|
| Source | `qml/`（M1）；`src/ui/` 预留给 C++ 桥接 |
| CMake | QML 挂在可执行目标 `minigcs` 的 `qt_add_qml_module` |
| Milestone | **M1** |
| Patterns | **P4**；将来绑 Vehicle/Fact 时 P1/P2 |

## Responsibility

- 顶层信息架构与页面切换  
- 展示态 UI；通过属性绑定消费 C++ 门面（有对象后）  

## Non-goals

- 解析 MAVLink、拥有 Link、写参数真源  

## M1 交付

| 文件 | 角色 |
|------|------|
| `Main.qml` | 主窗、导航、StackLayout |
| `FlyView.qml` | Fly 占位 |
| `PlanView.qml` | Plan 占位 |
| `AnalyzeView.qml` | Analyze 占位 |
| `SettingsView.qml` | App 设置占位 |

## QGC counterparts

- `MainWindow.qml`、`FlyView/`、`PlanView/`、抽屉工具页  
