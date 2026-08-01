# CURRENT — 实现侧交接单（MiniQGC）

> **在本仓新开对话时先读本文件。**  
> 设计课状态另见：`/Users/x_hoon/qgc_project/docs/learning/CURRENT.md`  
> 每次有效实现会话结束必须更新本文件。

---

## 一句话状态

**M-doc 完成；架构金科玉律 P1–P8 已定稿（ARCHITECTURE_PATTERNS + AGENTS）。下一步：CODING_STYLE 细则定稿 → 再 M0 实现。无业务代码。**

---

## 指针

| 项 | 值 |
|----|-----|
| 仓库 | https://github.com/threehoon/miniqgc |
| 本机路径 | `/Users/x_hoon/minigcs` |
| 详细进度 | [PROGRESS.md](PROGRESS.md) |
| 里程碑定义 | [MILESTONES.md](MILESTONES.md) |
| 设计课交接 | `../qgc_project/docs/learning/CURRENT.md` |
| 默认学法 | 设计课 → 本仓实现 → 收口（见 [AGENTS.md](../../AGENTS.md)） |

---

## 当前焦点

| 项 | 值 |
|----|-----|
| **当前里程碑** | 规范层 → 然后 **M0** |
| **M-doc** | ✅ 完成 |
| **架构模式 P1–P8** | ✅ 定稿（见 `docs/ARCHITECTURE_PATTERNS.md`） |
| **CODING_STYLE 细则** | ⬜ 提纲有，待对齐 QGC 补全 |
| **M0** | ⬜ 未开始 |
| **是否允许写业务代码** | 默认 **否** |

---

## 下一步

1. 设计课 / 本仓：定稿 **CODING_STYLE**（命名钉死、include、日志、QML）  
2. M0 设计复述 → 实现空壳  
3. 对照笔记 + 更新 CURRENT + push  

---

## 最近会话

| 项 | 内容 |
|----|------|
| 日期 | 2026-07-31 |
| 内容 | 定稿 Architecture Patterns P1–P8；重写 AGENTS 金科玉律短列表 |
| GitHub | 随本次 docs 提交推送 |

---

## 给 AI 的开场指令（可复制）

```text
请先读 docs/project/CURRENT.md 与 AGENTS.md。
本仓是作业本；设计课在 ../qgc_project/docs/learning/CURRENT.md。
当前 M-doc 已完成；不要开始 M0 业务代码，除非学员已完成设计课复述并明确要求实现。
```
