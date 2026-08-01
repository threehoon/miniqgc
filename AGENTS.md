# AGENTS.md — MiniQGC

面向在本仓库工作的 **AI 编程助手** 与 **人类开发者** 的约定说明。

## 项目定位

- **是什么**：体量可控、结构专业的迷你地面站（MiniQGC / MiniGCS），按竖切里程碑持续加功能。
- **为什么做**：沙盘练习——用正规工程方式内化与 QGC **同构**的框架/模块/调度纪律，最终服务 **基于 QGC 的客户向二次开发**。
- **不是什么**：
  - 不是功能对齐的完整 QGC 克隆  
  - **不是**「写个简单 demo 就结束」；功能可以少，**架构纪律与二开映射不能弱**  
- **主战场提醒**：客户交付仍在真 QGC / Custom Build；本仓每完成一刀应能对照「QGC 改哪里」。

## 学员开发习惯（教学与实现时尊重）

1. **先 Agent/契约文档与边界，再写代码**  
2. **模块化管理**是默认交付方式（CMake target + `docs/modules`）  
3. 保留 **中间调度层**（默认在 `src/app` / Application；UI 不直连 comms）  
4. 按专业权衡讨论设计，不把项目当一次性 demo  

设计课画像：`../qgc_project/docs/learning/LEARNER_PROFILE.md`。

## 默认学法（强制）

本仓是 **作业本**，不是设计课主场。

```text
① 设计课（qgc_project/docs/learning）— 探讨设计、为什么、带读 QGC
② 复述过关
③ 本仓实现 — 学员按自己的理解写代码
④ 收口对照 — 更新 CURRENT / PROGRESS / notes / git
```

| 仓 | 路径 | 角色 |
|----|------|------|
| 设计课 | `/Users/x_hoon/qgc_project/docs/learning/` | 框架设计、模块化、为什么 |
| 本仓 | `/Users/x_hoon/minigcs` | 实现与交付 |

规则：

1. 新对话先读 **[docs/project/CURRENT.md](docs/project/CURRENT.md)**，并核对设计课 `../qgc_project/docs/learning/CURRENT.md`。  
2. **设计课未复述过关前**，不要主动写该里程碑的业务代码（除非用户明确要求）。  
3. 实现以学员为主；避免整模块代写；卡住时先问卡点。  
4. 按 **从头做产品** 的顺序演进：框架 → 模块边界 → 启动 → 链路 → …  

设计课准则全文：`../qgc_project/docs/learning/README.md`。

## 参考项目（只读）

| 项 | 值 |
|----|-----|
| 绝对路径 | `/Users/x_hoon/qgc_project` |
| 相对路径（相对本仓根目录） | `../qgc_project` |
| 角色 | 架构与业务领域的对照标准 |
| 规则 | **不要为了 Mini 去改** QGC 应用代码。只读、对照；笔记可写本仓 `docs/learning/`。 |

路径与里程碑映射详见：[docs/REFERENCE.md](docs/REFERENCE.md)。

## 金科玉律

1. **模块边界** — 新代码必须落入所属模块（`comms`、`vehicle` 等）。禁止杂物堆。  
2. **依赖方向**（严格单向）：

   ```text
   apps → app/ui → vehicle/facts → comms/mavlink → core
   ```

   UI 不得解析 MAVLink；Comms 不得依赖 QML。  
3. **竖切交付** — 每个里程碑交付一条能跑通的链路，而不是半截分层空壳。  
4. **文档是产品的一部分** — 进度、问题、模块契约在 `docs/` 维护；行为变更时同步更新。  
5. **对照，不抄袭** — 每完成一条竖切，写明 QGC 如何做同一件事（文件入口 + 为何更复杂）。  
6. **不用 assert 撑生产逻辑** — 倾向防御性检查与清晰错误路径。  
7. **Vehicle 空指针纪律** — 使用 active/当前飞机指针前必须判空。  

## 文档权威源

| 关注点 | 权威文件 |
|--------|----------|
| **实现交接（新对话）** | **[docs/project/CURRENT.md](docs/project/CURRENT.md)** |
| 项目进度详情 | [docs/project/PROGRESS.md](docs/project/PROGRESS.md) |
| 未决问题 / 风险 | [docs/project/ISSUES.md](docs/project/ISSUES.md) |
| 里程碑定义 | [docs/project/MILESTONES.md](docs/project/MILESTONES.md) |
| 模块契约 | [docs/modules/](docs/modules/) |
| 架构 | [docs/architecture.md](docs/architecture.md) |
| 编码风格 | [docs/CODING_STYLE.md](docs/CODING_STYLE.md) |
| QGC 对照 | [docs/REFERENCE.md](docs/REFERENCE.md) |
| 学习笔记 | [docs/learning/](docs/learning/) |
| 设计决策 | [docs/decisions/](docs/decisions/) |
| 设计课交接 | `../qgc_project/docs/learning/CURRENT.md` |

结束一次有效会话时：更新 **CURRENT**、**PROGRESS**，必要时 **ISSUES / CHANGELOG**。

## 协作口令

| 口令 | 含义 |
|------|------|
| `进度` | 读两边 CURRENT 并汇报 |
| `问题` | 查看 / 整理 `docs/project/ISSUES.md` |
| `做 Mn` | 设计课过关或用户明确要求后，推进里程碑 n |
| `对照 QGC` | 映射当前竖切到参考仓，更新 learning notes |
| `更新进度` | 写 CURRENT / PROGRESS / CHANGELOG |
| `复述架构` | 学习者自述分层；对照 `architecture.md` 纠偏 |

## 实现策略

- **当前阶段**：M-doc 已完成；M0 等设计课 — **无明确授权不写业务代码**。  
- 提交信息使用 Conventional Commits：`feat`、`fix`、`docs`、`build`、`chore`、`refactor`、`test`。  
- 引入重大依赖前，先在 `docs/decisions/` 写 ADR。  
- 代码出现后，风格遵循 [docs/CODING_STYLE.md](docs/CODING_STYLE.md)。  

## 相关入口

- 人类总览：[README.md](README.md)  
- Claude 等助手：[CLAUDE.md](CLAUDE.md) → 本文件  
