# CURRENT — 实现侧交接单（MiniQGC）

> **新开对话请先读本文件**，再读下面的「必读文档」。

---

## 一句话状态

**M0 启动 + M1 导航壳 + M2 UDP Link 已完成；概念上已对齐「Link = 管道、串口/UDP 同级、非图传」。下一轮建议 M3 MAVLink 解析（或补 SerialLink）。**

---

## 新对话必读

| 顺序 | 文件 | 内容 |
|------|------|------|
| 1 | **本文件** | 进度与下一步 |
| 2 | [../learning/notes/m2-link-udp.md](../learning/notes/m2-link-udp.md) | Link/UDP/串口/图传对照（本轮核心） |
| 3 | [../ARCHITECTURE_PATTERNS.md](../ARCHITECTURE_PATTERNS.md) | 金科玉律 P1–P8 |
| 4 | [../../AGENTS.md](../../AGENTS.md) | Agent 总约定 |
| 5 | 设计课 CURRENT | `/Users/x_hoon/qgc_project/docs/learning/CURRENT.md` |

---

## 双仓

| 角色 | 路径 |
|------|------|
| 实现仓 | `/Users/x_hoon/minigcs` · https://github.com/threehoon/miniqgc |
| 参考 QGC | `/Users/x_hoon/qgc_project`（只读） |
| 设计课笔记 | `qgc_project/docs/learning/` |

---

## 协作方式（默认）

```text
① 先做出能看见的页面/效果
② 学员本地运行、点过
③ 学员说「看完了」
④ 再讲：功能 → 实现 → 模块 → 对照 QGC
```

学法总原则仍是：设计课（qgc 仓）→ 作业本（本仓）→ 收口。  
目标：服务 **QGC 客户向二次开发**，不是 demo 玩具。

---

## 里程碑看板

| ID | 内容 | 状态 |
|----|------|------|
| M-doc / Patterns | 文档 + P1–P8 | ✅ |
| M0 | main → Application → 窗口 | ✅ |
| M1 | 顶栏导航多页壳 | ✅ |
| M2 | `UdpLink` + Link 页 + 概念对齐 | ✅ |
| M3 | MAVLink（至少 HEARTBEAT） | ⬜ **建议下一轮** |
| M4 | Vehicle 对象 | ⬜ |
| — | SerialLink（真机串口） | ⬜ 可与 M3 后或并行 |

---

## 已建立的关键心智（勿回退）

1. **M0** = 启动流程（main 瘦，Application 调度根）  
2. **M1** = 顶栏导航切页（Fly/Plan/Link/Analyze/Settings）  
3. **Link** = 收发字节的管道；`start` 打开管道 ≠ 已有飞机  
4. **UDP** = 网络管道（仿真、Wi‑Fi 遥测等）；**不是**默认图传  
5. **SerialLink** = 同级串口管道（USB/数传呈串口）；Mini 未实现  
6. **图传** = 另一条业务线，与遥测 Link 分离  

---

## 构建与运行

```bash
cd /Users/x_hoon/minigcs
cmake --preset macos-qt6
cmake --build --preset macos-qt6
./build/apps/minigcs/MiniQGC.app/Contents/MacOS/MiniQGC
```

Qt 路径在 `CMakePresets.json` 的 `macos-qt6` 中，换机器需改或设 `CMAKE_PREFIX_PATH`。

Link 页自测：Start → `echo hello | nc -u -w1 127.0.0.1 14550` → 看 RX 日志。

---

## 下一轮学习建议（给新对话 AI）

1. 读本 CURRENT + `m2-link-udp.md`  
2. 与学员确认下一刀：**M3 解析** 或 **SerialLink**  
3. 仍 UI-first：先能看见效果，再讲模块  
4. 遵守 P4/P5/P6：解析不在 QML；Link 由 Application 创建  

---

## 最近会话

| 日期 | 内容 |
|------|------|
| 2026-07-31 | M0–M2 实现；UI-first 学法 |
| 2026-08-03 | 讲清串口/UDP/图传；UdpLink↔SerialLink 对照；**文档交接更新备新对话** |
