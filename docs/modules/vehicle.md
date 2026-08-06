# vehicle

| 字段 | 值 |
|------|-----|
| Source | `src/vehicle/` |
| CMake target | `mini_vehicle` |
| Milestone | **M4** |
| Patterns | **P2 可空**、P5、P6（app 创建）、P4（QML 只绑） |

## Responsibility

- 表示 **0 或 1 架**（M4）跟踪中的飞机运行时对象  
- 根据 HEARTBEAT **创建 / 更新** 状态  
- 暴露 `activeVehicle`（**可为 null**）给 UI  

## Non-goals

- 不拥有 socket（→ `comms`）  
- 不解析原始字节（→ `mavlink`）  
- 不渲染 UI  
- M4 不做多机列表 UI / 切换器（结构已按 sysid 预留）  

## M4 策略（已定）

| 项 | 决策 |
|----|------|
| 单机策略 | **先到先得（first-seen）**：第一架 HEARTBEAT 的 sysid 被跟踪 |
| 其它 sysid | 忽略并 debug 日志，直到当前机被 clear |
| 更新 | 同 sysid 心跳 → `applyHeartbeat` 刷新字段与时间戳 |
| 超时 | **5s** 无新心跳 → `clear()`（无飞机） |
| Link Stop | `runningChanged` → `clear()`，并解除 first-seen 锁定 |

以后多机：同一 Manager 按 sysid 持有多架 + `activeVehicle` 可切换；不必换 Parser。

## Public API (M4)

| 符号 | 说明 |
|------|------|
| `mini::vehicle::Vehicle` | 单机状态：sysId、type、autopilot、status… |
| `mini::vehicle::VehicleManager` | `handleHeartbeat` / `clear` / `activeVehicle` |
| Context property | `vehicleManager` |
| 判空 | `hasVehicle` 或 `activeVehicle !== null`（P2） |

## Depends on

- `mini_core`、Qt Core  
- **不**依赖 `comms` / QML  
- 消息语义由 app 从 `mavlink` 信号接入  

## Wiring (app)

```text
MavlinkParser::heartbeatReceived
  → VehicleManager::handleHeartbeat
UdpLink::runningChanged (false)
  → VehicleManager::clear
QML ← vehicleManager.activeVehicle (nullable)
```

## QGC counterparts

- `Vehicle`、`MultiVehicleManager::activeVehicle()`  
- 消息消费路径：`messageReceived` → Vehicle  

## Changelog

- M4：Vehicle + VehicleManager（first-seen 单机、5s 超时）+ Fly/顶栏可见  
