# Project management

本目录用 Markdown **维护 MiniGCS 项目本身**（不是业务代码注释的替代品）。

## 文件职责

| 文件 | 职责 | 更新频率 |
|------|------|----------|
| **[CURRENT.md](CURRENT.md)** | **新对话交接单**（做到哪、下一步） | 每次有效工作会话结束 |
| [PROGRESS.md](PROGRESS.md) | 进度详情与看板 | 同上 |
| [MILESTONES.md](MILESTONES.md) | 里程碑定义与验收标准 | 规划变更时 |
| [ISSUES.md](ISSUES.md) | 问题、风险、阻塞、待决 | 发现或关闭时 |
| [CHANGELOG.md](CHANGELOG.md) | 已发生的变更摘要 | 有可感知进展时 |
| [SESSION_LOG.md](SESSION_LOG.md) | 学习/开发会话流水（可选详细） | 按需 |

设计课交接（另一仓）：`/Users/x_hoon/qgc_project/docs/learning/CURRENT.md`。

## 工作流（设计课 → 作业本）

```text
开始工作
  → 读本仓 CURRENT + 设计课 CURRENT
  → 若设计课未过关：提醒去 qgc_project 探讨，默认不写业务代码
  → 若可实现：确认 MILESTONES 验收 → 实现
  → 更新 CURRENT、PROGRESS、ISSUES、必要时 CHANGELOG
  → git commit（需要时 push）
```

## 与 learning 的分工

| 目录 | 管什么 |
|------|--------|
| `docs/project/` | **项目交付**：里程碑、进度、问题、changelog |
| `docs/learning/` | **对照学习**：相对 QGC 的业务理解、代码映射笔记 |
| `docs/modules/` | **模块契约**：接口意图、边界、依赖 |
| `docs/decisions/` | **决策**：为什么选 A 不选 B |

三者互补；进度只信 `PROGRESS.md`。
