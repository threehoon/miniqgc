# comms

| 字段 | 值 |
|------|-----|
| Source | `src/comms/` |
| CMake target (planned) | `mini_comms` |
| First milestone | M2 |

## Responsibility

- 链路抽象：连接、断开、读写字节
- 具体传输：UDP 优先，Serial 后置

## Non-goals

- 不解析 MAVLink 帧语义（交给 `mavlink`）
- 不创建 Vehicle

## Depends on

- `core` only

## Public concepts (planned)

- `Link` 接口（或抽象基类）
- `UdpLink` 实现
- 连接配置（host/port 等）

## Threading notes

- IO 不在 GUI 线程阻塞；向上层投递字节用线程安全队列或 queued signal

## QGC counterparts

- `src/Comms/LinkManager`、`UDPLink`、`SerialLink`、…

## Open questions

- 是否需要 LinkManager 多链路 — M2 可先单链路，多链路 ADR 后再加
