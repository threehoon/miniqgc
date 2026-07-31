# mavlink

| 字段 | 值 |
|------|-----|
| Source | `src/mavlink/` |
| CMake target (planned) | `mini_mavlink` |
| First milestone | M3 |

## Responsibility

- 字节流 → MAVLink 消息；消息 → 字节
- 至少支持 HEARTBEAT 等最小集合

## Non-goals

- 不管理 socket
- 不实现完整任务协议 UI

## Depends on

- `core`；使用何种 MAVLink C 库 — 见 decisions ADR（M3 前）

## Public concepts (planned)

- `Parser` / `Codec`
- 对上层友好的消息视图（不强行暴露全部生成代码）

## Threading notes

- 解析可在 IO 或专用线程；发布到 vehicle 需线程边界清晰

## QGC counterparts

- `src/MAVLink/`、Vehicle 内 message handlers

## Open questions

- 使用官方 mavlink 生成头 vs 第三方封装 — **M3 前必须 ADR**
