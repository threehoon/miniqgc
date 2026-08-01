# Milestones

功能按竖切里程碑交付。每个里程碑必须：**可演示 + 文档更新 + 不破坏模块边界**。

**学法**：设计课（qgc_project）过关 → 本仓实现 → 收口。见根目录 [AGENTS.md](../../AGENTS.md)。

## Status legend

| 标记 | 含义 |
|------|------|
| `todo` | 未开始 |
| `active` | 当前焦点 |
| `done` | 验收通过 |
| `blocked` | 有阻塞（见 ISSUES） |

---

## M-doc — Documentation & tree scaffold

| 项 | 内容 |
|----|------|
| Status | `done` |
| Goal | 独立仓库、Git、Agent 文档、项目管理 MD、占位目录 |
| Acceptance | 目录可导航；进度/问题/模块文档齐；已推送 GitHub |

---

## M0 — Build skeleton (empty app)

| 项 | 内容 |
|----|------|
| Status | **`done`**（2026-07-31） |
| Goal | CMake + Qt 工程可配置；空窗口或最小 Application 能启动 |
| Delivered | `mini_core` / `mini_app` / `minigcs`；`Application`；`qml/Main.qml`；presets |
| Out of scope | 通信、MAVLink、真飞数据 |
| Acceptance | 本机 configure+build+加载主窗；CURRENT 已更新 |
| QGC 对照 | `main.cc`、`QGCApplication`、根 CMake |
| Run | `cmake --preset macos-qt6 && cmake --build --preset macos-qt6` |

---

## M1 — Shell UI

| 项 | 内容 |
|----|------|
| Status | **`done`**（2026-07-31） |
| Goal | 主窗 + 假页面切换（Fly / Plan / Analyze / Settings） |
| Delivered | `Main.qml` 顶栏 + StackLayout；四页占位 QML |
| Acceptance | 能切换页面；UI 仅壳层；启动链仍在 app |
| QGC 对照 | `MainWindow.qml`（Mini 用顶栏 Tab 简化 toolDrawer） |
| Notes | `docs/learning/notes/m1-shell-ui.md` |

---

## M2 — Comms link (bytes)

| 项 | 内容 |
|----|------|
| Status | `todo` |
| Goal | `comms` 模块：UDP（优先）收发原始字节；日志可见 |
| Acceptance | 用 nc/SITL/自写 sender 能看到收包日志 |
| QGC 对照 | `src/Comms/` |

---

## M3 — MAVLink parse

| 项 | 内容 |
|----|------|
| Status | `todo` |
| Goal | 解析至少 HEARTBEAT |
| Acceptance | 日志或结构体中打印 sysid/compid/type/autopilot |
| QGC 对照 | MAVLink 处理路径 |

---

## M4 — Vehicle object

| 项 | 内容 |
|----|------|
| Status | `todo` |
| Goal | 心跳 → 创建/更新 `Vehicle` |
| Acceptance | 内存中有明确 Vehicle 生命周期；断开策略有文档 |
| QGC 对照 | `Vehicle` / MultiVehicle |

---

## M5 — UI binding

| 项 | 内容 |
|----|------|
| Status | `todo` |
| Goal | 界面显示连接状态与 1～2 个字段（如 mode） |
| Acceptance | 无飞机 / 有飞机 UI 可区分 |
| QGC 对照 | Fly 相关属性绑定 |

---

## M6 — Facts (lite)

| 项 | 内容 |
|----|------|
| Status | `todo` |
| Goal | 极简 Fact：统一读遥测/假参数 |
| Acceptance | UI 不直读 MAVLink 字段；经 Fact 或等价层 |
| QGC 对照 | `FactSystem` |

---

## M7+ — Later

任务、命令、串口、多机、设置页、插件化等 — 在 M6 后再拆分具体里程碑，写入本文件。

---

## Definition of Done（每个里程碑通用）

1. 设计课要点已复述（或用户书面确认跳过）  
2. 验收标准全部满足  
3. [CURRENT.md](CURRENT.md) 与 [PROGRESS.md](PROGRESS.md) 已更新  
4. 相关 [modules/](../modules/) 契约已写或修订  
5. 有对照笔记（[learning/notes/](../learning/notes/)）或明确跳过理由  
6. Git 有清晰 commit（需要时 push）  
