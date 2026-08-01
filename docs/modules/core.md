# core

| 字段 | 值 |
|------|-----|
| Source | `src/core/` |
| CMake target | `mini_core` |
| First milestone | **M0** |
| Patterns | P5（无业务）、P8（日志） |

## Responsibility

- 跨模块共享的基础能力  
- **分类日志**声明与约定（`mini.*`）  
- 不依赖业务域的通用工具（按需扩展）  

## Non-goals

- 链路、飞机、UI、调度组装  

## Depends on

- Qt Core  
- **不得**依赖其它 `mini_*` 模块  

## Public API (M0)

| 符号 | 说明 |
|------|------|
| `namespace mini::core` | 模块命名空间 |
| `MiniCoreLog` | 日志 category：`mini.core` |
| 头文件 `Logging.h` | 声明/定义日志 category 的入口 |

## Threading

- 日志 API 遵循 Qt 约定  

## QGC counterparts

- Utilities / `QGCLoggingCategory` 等；Mini 收敛到 `core`  

## Changelog

- M0：落地 `mini_core` + `Logging.h`  
