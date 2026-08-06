# mavlink

| 字段 | 值 |
|------|-----|
| Source | `src/mavlink/` |
| CMake target | `mini_mavlink` |
| Milestone | **M3** |
| Patterns | P4（QML 不解析）、P5、P6（app 创建/接线） |
| Library ADR | [../decisions/0001-mavlink-library-choice.md](../decisions/0001-mavlink-library-choice.md) |

## Responsibility

- 字节流 → MAVLink 帧/消息（`mavlink_parse_char`）
- 至少解码 **HEARTBEAT**，向 UI / 将来 Vehicle 暴露字段
- 可选：将来消息 → 字节（encode/send）

## Non-goals

- 不管理 socket / 串口（→ `comms`）
- 不创建 Vehicle（→ `vehicle` / M4）
- 不实现完整任务/参数协议 UI
- QML 内禁止拆帧

## Public API (M3)

| 符号 | 说明 |
|------|------|
| `mini::mavlink::MavlinkParser` | QObject：`feed` / `clearLog` / `reset` |
| 统计属性 | `messagesParsed`、`heartbeatsParsed`、`parseErrors` |
| 最近心跳 | `lastSysId` / `lastCompId` / `lastType` / `lastAutopilot` / `lastBaseMode` / `lastCustomMode` / `lastSystemStatus` / `hasHeartbeat` |
| 日志 | `logLines`（HEARTBEAT 可读行） |
| 信号 | `heartbeatReceived(...)`（供 M4 接线） |
| Context property | `mavlinkParser`（`Application` 注入） |

## Depends on

- `mini_core`
- Qt Core
- `mavlink/c_library_v2`（FetchContent，INTERFACE 头）
- **不得**依赖 `ui` / QML / `comms`（只吃 `QByteArray`）

## Wiring (app)

```text
UdpLink::datagramReceived(data, …)
  → Application 连接
  → MavlinkParser::feed(data)
  → QML 绑定 mavlinkParser.*
```

## QGC counterparts

| Mini | QGC |
|------|-----|
| `c_library_v2` | CPM mavlink 生成头 |
| `MavlinkLib.h` | `src/MAVLink/MAVLinkLib.h` |
| `MavlinkParser` | `MAVLinkProtocol`（简化：单通道、先 HEARTBEAT） |
| `heartbeatReceived` | `MAVLinkProtocol::messageReceived` → `Vehicle::_mavlinkMessageReceived` |

## Changelog

- M3：官方头 + `MavlinkParser` + Link/Analyze 可见 HEARTBEAT
