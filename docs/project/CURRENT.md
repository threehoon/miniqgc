# CURRENT — 实现侧交接单（MiniQGC）

> **在本仓新开对话时先读本文件。**

---

## 一句话状态

**规范 P1–P8 + CODING_STYLE 已落地；M0 空壳已实现并通过本机构建与 QML 加载冒烟。下一里程碑 M1（Shell UI）或按设计课继续。**

---

## 指针

| 项 | 值 |
|----|-----|
| 仓库 | https://github.com/threehoon/miniqgc |
| 本机路径 | `/Users/x_hoon/minigcs` |
| 金科玉律 | [../ARCHITECTURE_PATTERNS.md](../ARCHITECTURE_PATTERNS.md) |
| Agent | [../../AGENTS.md](../../AGENTS.md) |
| 风格 | [../CODING_STYLE.md](../CODING_STYLE.md) |
| 设计课 | `../qgc_project/docs/learning/CURRENT.md` |

---

## 当前焦点

| 项 | 值 |
|----|-----|
| **M-doc** | ✅ |
| **Architecture Patterns** | ✅ P1–P8 |
| **CODING_STYLE** | ✅ M0 强制版 |
| **M0** | ✅ 可配置 / 编译 / 加载主窗 |
| **M1** | ⬜ 未开始 |

### M0 验收

- [x] CMake targets：`mini_core`、`mini_app`、`minigcs`  
- [x] `main` → `Application::init` → `loadFromModule(MiniQGC, Main)` → `exec`  
- [x] 分类日志 `mini.app` / `mini.core`  
- [x] 本机 `cmake --preset macos-qt6 && cmake --build --preset macos-qt6`  
- [x] offscreen 冒烟：`init: root UI ready`  

运行：

```bash
cmake --preset macos-qt6 && cmake --build --preset macos-qt6
./build/apps/minigcs/MiniQGC.app/Contents/MacOS/MiniQGC
```

---

## 下一步

1. M1 设计课：主窗信息架构 / 假页面切换  
2. 或补 `docs/learning/notes/m0-bootstrap.md` 对照 QGC 启动链  
3. 需要时把 `CMakePresets` 中 Qt 路径改为可移植写法  

---

## 最近会话

| 项 | 内容 |
|----|------|
| 日期 | 2026-07-31 |
| 内容 | 同步文档至 P1–P8；实现并验证 M0 |
