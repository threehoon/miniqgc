# AGENTS.md — MiniGCS

面向在本仓库工作的 **AI 编程助手** 与 **人类开发者** 的约定说明。

## 项目定位

- **是什么**：体量可控、结构专业的迷你地面站（MiniGCS），按竖切里程碑持续加功能。
- **为什么做**：用正规工程方式（CMake、模块边界、文档、Git）搭一套与 QGroundControl **同构的小系统**，在实现中学习 QGC 的架构与领域。
- **不是什么**：不是功能对齐的 QGC 克隆。优先正确边界与可演进结构，而不是功能数量。

## 参考项目（只读）

| 项 | 值 |
|----|-----|
| 绝对路径 | `/Users/x_hoon/qgc_project` |
| 相对路径（相对本仓根目录） | `../qgc_project` |
| 角色 | 架构与业务领域的对照标准 |
| 规则 | **不要为了 Mini 去改** QGC 应用代码。只读、对照，笔记写在本仓。 |

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
6. **不用 assert 撑生产逻辑** — 倾向防御性检查与清晰错误路径（对齐 QGC 代理规范精神）。
7. **Vehicle 空指针纪律** — 使用 active/当前飞机指针前必须判空（尽早养成 Multi-Vehicle 习惯）。

## 文档权威源

| 关注点 | 权威文件 |
|--------|----------|
| 项目进度 | [docs/project/PROGRESS.md](docs/project/PROGRESS.md) |
| 未决问题 / 风险 | [docs/project/ISSUES.md](docs/project/ISSUES.md) |
| 里程碑定义 | [docs/project/MILESTONES.md](docs/project/MILESTONES.md) |
| 模块契约 | [docs/modules/](docs/modules/) |
| 架构 | [docs/architecture.md](docs/architecture.md) |
| 编码风格 | [docs/CODING_STYLE.md](docs/CODING_STYLE.md) |
| QGC 对照 | [docs/REFERENCE.md](docs/REFERENCE.md) |
| 学习笔记 | [docs/learning/](docs/learning/) |
| 设计决策 | [docs/decisions/](docs/decisions/) |

结束一次有效会话时：若有进展，更新 **PROGRESS** 与 **ISSUES**。

## 协作口令（可选）

| 口令 | 含义 |
|------|------|
| `进度` | 根据 `docs/project/PROGRESS.md` 汇报 |
| `问题` | 查看 / 整理 `docs/project/ISSUES.md` |
| `做 Mn` | 按 `MILESTONES.md` 推进第 n 个里程碑 |
| `对照 QGC` | 映射当前竖切到 `../qgc_project`，并更新 learning 笔记 |
| `更新进度` | 将会话结果写入 PROGRESS / CHANGELOG |
| `复述架构` | 学习者自述分层；对照 `architecture.md` 纠偏 |

## 实现策略

- **当前阶段**：仅文档与目录框架 — **在用户明确要求前不要写业务代码**。
- 提交信息使用 Conventional Commits：`feat`、`fix`、`docs`、`build`、`chore`、`refactor`、`test`。
- 引入重大依赖前，先在 `docs/decisions/` 写 ADR。
- 代码出现后，风格遵循 [docs/CODING_STYLE.md](docs/CODING_STYLE.md)。

## 相关入口

- 人类总览：[README.md](README.md)
- Claude 等助手：[CLAUDE.md](CLAUDE.md) → 本文件
