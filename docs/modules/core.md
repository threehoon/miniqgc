# core

| 字段 | 值 |
|------|-----|
| Source | `src/core/` |
| CMake target (planned) | `mini_core` |
| First milestone | M0 |

## Responsibility

- 跨模块共享的基础类型与工具
- 日志门面 / 分类 logger 约定
- 不依赖业务域的错误与通用工具

## Non-goals

- 不包含链路、飞机、UI
- 不拉取网络或硬件

## Depends on

- Qt Core（按需）、C++ 标准库  
- **不得**依赖其他 `mini_*` 业务模块

## Public concepts (planned)

- 命名空间 `mini::core`
- 日志类别前缀 `mini.*`
- （可选）Result / 错误码风格 — ADR 再定

## Threading notes

- 工具函数默认线程安全或明确文档为否

## QGC counterparts

- 分散在 Utilities、日志宏等；Mini 刻意收敛到 `core`

## Open questions

- 成员命名 `_foo` vs `foo_` — M0 定一种写入 CODING_STYLE
