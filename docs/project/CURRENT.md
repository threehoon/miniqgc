# CURRENT — 实现侧交接单（MiniQGC）

> **在本仓新开对话时先读本文件。**

---

## 一句话状态

**M0 + M1 已完成：启动链 + 主窗四页切换（Fly/Plan/Analyze/Settings 占位）。下一刀倾向 M2 通信（UDP 字节）。**

---

## 指针

| 项 | 值 |
|----|-----|
| 仓库 | https://github.com/threehoon/miniqgc |
| 本机 | `/Users/x_hoon/minigcs` |
| 金律 | `docs/ARCHITECTURE_PATTERNS.md` |
| 笔记 | `docs/learning/notes/m1-shell-ui.md` |

---

## 里程碑

| ID | 状态 |
|----|------|
| M0 启动空壳 | ✅ |
| M1 Shell UI | ✅ |
| M2 Comms bytes | ⬜ 下一步 |

### M1 验收

- [x] 顶栏 Fly / Plan / Analyze / Settings  
- [x] `StackLayout` 切换，标题与底栏同步  
- [x] 底栏提示无 vehicle（P2）  
- [x] 构建 + 冒烟加载成功  
- [x] Fusion 样式避免 macOS 原生控件定制警告  

```bash
cmake --preset macos-qt6 && cmake --build --preset macos-qt6
./build/apps/minigcs/MiniQGC.app/Contents/MacOS/MiniQGC
```

---

## 下一步

1. **M2 设计/实现**：`comms` 模块 UDP 收字节 + 日志（仍由 Application 创建接线，P6）  
2. 可选：把 Analyze/Settings 改成 QGC 式抽屉（非必须）  

---

## 最近会话

| 日期 | 内容 |
|------|------|
| 2026-07-31 | M1 主窗四页壳 + 文档 |
