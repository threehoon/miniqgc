# comms

| 字段 | 值 |
|------|-----|
| Source | `src/comms/` |
| CMake target | `mini_comms` |
| Milestone | **M2** |
| Patterns | P5、P6（由 app 创建）、P4（QML 只绑定） |

## Responsibility

- 链路字节 IO（当前：UDP 监听与收包）  
- 向 UI 暴露状态与收包日志；向后续模块发 `datagramReceived`  

## Non-goals

- MAVLink 解析（M3）  
- 创建 Vehicle  

## Public API (M2)

| 类型 | 说明 |
|------|------|
| `mini::comms::UdpLink` | QObject；`start`/`stop`；统计与 `logLines` |
| Context property | `udpLink`（Application 注入） |

## QGC counterparts

- `src/Comms/UDPLink`、`LinkManager`  
