# Issues / Risks / Open questions

> 项目级问题台账。关闭时把状态改为 `closed` 并写一行结论，不要默默删除历史。

## How to use

| 字段 | 说明 |
|------|------|
| ID | `ISS-001` 递增 |
| Status | `open` / `blocked` / `closed` |
| Severity | `low` / `med` / `high` |
| Area | `build` / `arch` / `docs` / `comms` / … |

---

## Open

### ISS-001 — Qt / CMake 本机环境未在 Mini 仓验证

| 字段 | 值 |
|------|-----|
| Status | `open` |
| Severity | `med` |
| Area | `build` |
| Created | 2026-07-31 |

**现象**：M0 尚未开始；QGC 仓曾可构建不代表 Mini 预设一次成功。  

**影响**：M0 验收可能卡在工具链。  

**缓解**：M0 时对照 `../qgc_project` 的 Qt 版本；记录实际版本到 PROGRESS。

---

### ISS-002 — 学习笔记双仓是否合并

| 字段 | 值 |
|------|-----|
| Status | `open` |
| Severity | `low` |
| Area | `docs` |
| Created | 2026-07-31 |

**现象**：QGC 仓已有 `docs/learning/`；Mini 也建了 `docs/learning/`。  

**选项**：  
A) 新笔记只写 Mini（推荐）  
B) 继续只写 QGC 仓  
C) 两边都写（易分叉，不推荐）  

**结论**：待用户决定。

---

## Closed

（暂无）

---

## Risk register（非缺陷）

| ID | Risk | Mitigation |
|----|------|------------|
| R-01 | 做成「第二个大 QGC」导致无法交付 | 严守 MILESTONES 范围；禁止提前做视频/3D/完整 Setup |
| R-02 | 只写代码不写对照笔记，学不到 QGC | DoD 强制 learning note 或显式跳过理由 |
| R-03 | 模块边界腐烂 | 依赖方向写在 architecture；MR 自检表 |
