# Modules — contracts index

每个源码模块一份契约文档。实现前先写清 **职责 / 非职责 / 依赖 / 公开概念**；实现后保持同步。

| 模块 | 源码目录 | 契约文档 | 计划首现 |
|------|----------|----------|----------|
| core | `src/core/` | [core.md](core.md) | M0 |
| app | `src/app/` | [app.md](app.md) | M0 |
| ui | `src/ui/` + `qml/` | [ui.md](ui.md) | M1 |
| comms | `src/comms/` | [comms.md](comms.md) | M2 |
| mavlink | `src/mavlink/` | [mavlink.md](mavlink.md) | M3 |
| vehicle | `src/vehicle/` | [vehicle.md](vehicle.md) | M4 |
| facts | `src/facts/` | [facts.md](facts.md) | M6 |

## 契约模板（新模块复制）

```markdown
# module-name

## Responsibility
## Non-goals
## Depends on
## Public concepts (types / services)
## Threading notes
## QGC counterparts
## Open questions
```
