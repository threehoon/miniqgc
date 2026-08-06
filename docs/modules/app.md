# app

| 字段 | 值 |
|------|-----|
| Source | `src/app/` |
| CMake target | `mini_app` |
| First milestone | **M0**（接线随 M2/M3 扩展） |
| Patterns | **P6 调度层**、P4（加载 QML）、P5、P8 |

## Responsibility

- 应用生命周期：`init` / `exec` / `shutdown`  
- **调度 / 组装根**（P6）：创建并接线 domain 模块  
- 加载根 QML、持有 `QQmlApplicationEngine`  
- 向 QML 注入 context property（`udpLink`、`mavlinkParser`…）  

## Non-goals

- 协议算法细节（在 `mavlink`）  
- socket IO 实现（在 `comms`）  
- 飞控业务状态机（在 `vehicle`，M4）  

## Depends on

- `mini_core`、`mini_comms`、`mini_mavlink`  
- Qt：Gui、Qml、Quick  

## Public API

| 符号 | 说明 |
|------|------|
| `mini::app::Application` | 继承 `QGuiApplication`；组装根 |
| `init()` | 创建服务、接线、加载根界面 |
| `shutdown()` | 有序清理 |
| `udpLink()` / `mavlinkParser()` | 已创建服务访问 |
| 日志 | `MiniAppLog` → `mini.app` |

## Wiring (current)

```text
Application::init
  → new UdpLink, MavlinkParser, VehicleManager
  → datagramReceived → parser.feed
  → heartbeatReceived → vehicleManager.handleHeartbeat
  → link !running → vehicleManager.clear
  → setContextProperty udpLink / mavlinkParser / vehicleManager
  → load Main.qml
```

## QGC counterparts

- `QGCApplication`、`main.cc` 启动链  

## Changelog

- M0：`Application` 空壳 + 加载根 QML  
- M2：创建/注入 `UdpLink`  
- M3：创建/注入 `MavlinkParser`，接线 `datagramReceived → feed`  
- M4：创建/注入 `VehicleManager`，接线心跳与 Link Stop  

