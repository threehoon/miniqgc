# ui

| 字段 | 值 |
|------|-----|
| Source | `src/ui/` + `qml/` |
| CMake target (planned) | `mini_ui` |
| First milestone | M1 |

## Responsibility

- QML 界面与 C++ 展示模型 / 控制器
- 用户可见状态绑定

## Non-goals

- 不解析 MAVLink
- 不直接操作 socket

## Depends on

- `core`；只读/调用 `vehicle` / `facts` 的公开 API

## Public concepts (planned)

- 根 `Main.qml`
- 页面占位：Fly / Plan（名称可调）
- C++ 侧 bridge 类型

## Threading notes

- QML 与 model 更新在 GUI 线程；跨线程必须用信号槽队列

## QGC counterparts

- `MainWindow.qml`、`FlyView/`、`PlanView/`、`QmlControls/`

## Open questions

- 是否使用 QML 模块 URI（如 `MiniGCS`）— M1 定
