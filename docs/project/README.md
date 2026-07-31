# Project management

本目录用 Markdown **维护 MiniGCS 项目本身**（不是业务代码注释的替代品）。

## 文件职责

| 文件 | 职责 | 更新频率 |
|------|------|----------|
| [PROGRESS.md](PROGRESS.md) | **唯一**进度权威：现在做到哪、下一步是什么 | 每次有效工作会话结束 |
| [MILESTONES.md](MILESTONES.md) | 里程碑定义与验收标准 | 规划变更时 |
| [ISSUES.md](ISSUES.md) | 问题、风险、阻塞、待决 | 发现或关闭时 |
| [CHANGELOG.md](CHANGELOG.md) | 已发生的变更摘要 | 有可感知进展时 |
| [SESSION_LOG.md](SESSION_LOG.md) | 学习/开发会话流水（可选详细） | 按需 |

## 工作流（专业小团队习惯）

```text
开始工作
  → 读 PROGRESS + ISSUES
  → 确认当前里程碑验收标准（MILESTONES）
  → 实现 / 文档
  → 更新 PROGRESS、ISSUES、必要时 CHANGELOG
  → git commit
```

## 与 learning 的分工

| 目录 | 管什么 |
|------|--------|
| `docs/project/` | **项目交付**：里程碑、进度、问题、changelog |
| `docs/learning/` | **对照学习**：相对 QGC 的业务理解、代码映射笔记 |
| `docs/modules/` | **模块契约**：接口意图、边界、依赖 |
| `docs/decisions/` | **决策**：为什么选 A 不选 B |

三者互补；进度只信 `PROGRESS.md`。
