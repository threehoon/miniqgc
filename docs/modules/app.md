# app

| 字段 | 值 |
|------|-----|
| Source | `src/app/` |
| CMake target (planned) | `mini_app` |
| First milestone | M0 |

## Responsibility

- 应用生命周期：启动、退出、全局服务组装（composition root）
- 创建根 QML / 主窗口
- 把各模块实例「接线」到一起

## Non-goals

- 不实现具体链路协议细节
- 不在 app 里堆业务算法

## Depends on

- `core`；随里程碑链接 `ui` / `vehicle` / `comms` 等

## Public concepts (planned)

- `Application`（或同等）类
- 全局可访问的受控入口（避免无文档单例）

## Threading notes

- 构造与 UI 相关初始化在 GUI 线程

## QGC counterparts

- `QGCApplication`、`main.cc` 启动链

## Open questions

- 是否采用显式 `Context` 对象注入 vs 少量单例 — M0/M1 决策
