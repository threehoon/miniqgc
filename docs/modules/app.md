# app

| 字段 | 值 |
|------|-----|
| Source | `src/app/` |
| CMake target | `mini_app` |
| First milestone | **M0** |
| Patterns | **P6 调度层**、P4（加载 QML）、P5、P8 |

## Responsibility

- 应用生命周期：`init` / `exec` / `shutdown`  
- **调度 / 组装根**（P6）：后续创建并接线 comms/vehicle…  
- 加载根 QML、持有 `QQmlApplicationEngine`  

## Non-goals

- 协议解析、socket IO、飞控业务算法  

## Depends on

- `mini_core`  
- Qt：Gui、Qml、Quick  
- M0 **不**链接 comms/vehicle（尚未实现）  

## Public API (M0)

| 符号 | 说明 |
|------|------|
| `mini::app::Application` | 继承 `QGuiApplication`；组装根 |
| `init()` | 加载根界面；失败返回 false |
| `shutdown()` | 有序清理 |
| 日志 | `MiniAppLog` → `mini.app` |

## Threading

- 构造与 `init` 在 GUI 线程  

## QGC counterparts

- `QGCApplication`、`main.cc` 启动链  

## Changelog

- M0：`Application` 空壳 + 加载 `qrc:/qt/qml/MiniQGC/Main.qml` 或等价根 QML  
