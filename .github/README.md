# `.github/` — GitHub 协作与自动化

本目录存放与 **GitHub 仓库协作、CI、社区模板** 相关的配置，与业务源码分离。

| 项 | 说明 |
|----|------|
| 所属项目 | [MiniQGC](https://github.com/threehoon/miniqgc) |
| 当前状态 | **占位阶段**：尚未启用工作流或 Issue 模板 |
| 主文档入口 | 仓库根目录 [README.md](../README.md) |

---

## 目录用途

| 路径（规划） | 作用 |
|--------------|------|
| `workflows/` | GitHub Actions（配置、构建、测试、文档检查等） |
| `ISSUE_TEMPLATE/` | Issue 模板（缺陷 / 需求 / 问题） |
| `PULL_REQUEST_TEMPLATE.md` | PR 描述模板 |
| `CODEOWNERS` | （可选）代码评审责任人 |
| `dependabot.yml` | （可选）依赖更新 |

以上文件 **按需添加**，未创建前请勿假设 CI 已运行。

## 现状与计划

| 阶段 | 内容 | 状态 |
|------|------|------|
| 现在 | 仅本说明文件，不跑任何 Action | 已就位 |
| M0 之后 | 可选：配置/编译冒烟 workflow（`cmake` + 空壳构建） | 未开始 |
| 持续 | 有需要时再补 PR/Issue 模板 | 按需 |

原则：

1. **先本地能编，再上 CI** — 避免为红灯维护流水线  
2. **工作流保持精简** — 只覆盖当前里程碑真正用到的检查  
3. **密钥不上库** — 任何 token、本机路径写在 GitHub Secrets / 本地忽略文件中  

## 与项目文档的关系

- 构建与里程碑验收：`docs/project/MILESTONES.md`、`docs/project/PROGRESS.md`  
- 开发约定：`AGENTS.md`、`docs/CODING_STYLE.md`  
- 本目录只负责 **GitHub 平台侧** 自动化与协作模板，不重复写架构说明  

## 何时添加第一个 workflow

建议满足以下条件后再加：

- [ ] M0 在本机可稳定 `configure + build`  
- [ ] 有一条固定、可文档化的构建命令  
- [ ] 明确 CI 机器镜像（如 Ubuntu + Qt 版本）  

届时在 `workflows/` 下新增例如 `ci.yml`，并在本 README 的「现状与计划」中更新状态。
