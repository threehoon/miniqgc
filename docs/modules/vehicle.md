# vehicle

| 字段 | 值 |
|------|-----|
| Source | `src/vehicle/` |
| CMake target (planned) | `mini_vehicle` |
| First milestone | M4 |

## Responsibility

- 表示一架（或后期多架）飞机的运行时对象
- 处理与「这架飞机」相关的消息与状态
- 多机时的 active 选择（后期）

## Non-goals

- 不拥有原始 socket
- 不渲染 UI

## Depends on

- `core`、`mavlink`；通过信号/接口消费 `comms` 的字节或已解析消息

## Public concepts (planned)

- `Vehicle`
- （后期）`MultiVehicleManager` 或同等
- **使用前空指针检查** 纪律

## Threading notes

- 对外属性更新最终在 GUI 线程可见（Qt 模型规则）

## QGC counterparts

- `src/Vehicle/Vehicle.*`、MultiVehicle 相关

## Open questions

- 心跳超时删车策略；单机版是否仍保留 Manager 空壳 — M4 定
