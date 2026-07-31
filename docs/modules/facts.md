# facts

| 字段 | 值 |
|------|-----|
| Source | `src/facts/` |
| CMake target (planned) | `mini_facts` |
| First milestone | M6 |

## Responsibility

- 统一「值 + 元数据」模型：遥测与（简化）参数
- 给 UI 绑定，避免界面直接啃协议字段

## Non-goals

- M6 不做完整 PX4/APM 参数元数据生态
- 不替代 Settings（应用设置可另模块）

## Depends on

- `core`；与 `vehicle` 的关系在实现时写清（组合 vs 旁路）

## Public concepts (planned)

- `Fact`（name、value、type、可选 limits）
- 少量内置遥测 Fact

## Threading notes

- 值变更通知对 QML 安全

## QGC counterparts

- `src/FactSystem/` — Mini 只学思想，规模缩小

## Open questions

- 参数写入回传链路放 vehicle 还是 facts — M6 ADR
