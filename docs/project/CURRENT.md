# CURRENT — 实现侧交接单（MiniQGC）

> **新开对话请先读本文件**，再读下面的「必读文档」。

---

## 一句话状态

**M0–M3 已实现：启动壳 + 导航 + UdpLink + MAVLink HEARTBEAT 解析。**  
下一轮建议 **M4 Vehicle**（或补 SerialLink）。学员侧：先跑通 Link 页心跳，再讲本轮设计。

---

## 新对话必读

| 顺序 | 文件 | 内容 |
|------|------|------|
| 1 | **本文件** | 进度与下一步 |
| 2 | [../learning/notes/m3-mavlink-parse.md](../learning/notes/m3-mavlink-parse.md) | M3 概念（本轮） |
| 3 | [../learning/notes/m2-link-udp.md](../learning/notes/m2-link-udp.md) | Link 管道（前序） |
| 4 | [../decisions/0001-mavlink-library-choice.md](../decisions/0001-mavlink-library-choice.md) | 官方 mavlink 头 |
| 5 | [../ARCHITECTURE_PATTERNS.md](../ARCHITECTURE_PATTERNS.md) | 金科玉律 P1–P8 |
| 6 | 设计课 CURRENT | `/Users/x_hoon/qgc_project/docs/learning/CURRENT.md` |

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

---

## 里程碑看板

| ID | 内容 | 状态 |
|----|------|------|
| M-doc / Patterns | 文档 + P1–P8 | ✅ |
| M0 | main → Application → 窗口 | ✅ |
| M1 | 顶栏导航多页壳 | ✅ |
| M2 | `UdpLink` + Link 页 | ✅ |
| M3 | `MavlinkParser` + HEARTBEAT UI | ✅ **本轮交付代码** |
| M4 | Vehicle 对象 | ⬜ **建议下一轮** |
| — | SerialLink | ⬜ 可并行 |

---

## 已建立的关键心智（勿回退）

1. **Link** = 字节管道；Start ≠ 有飞机  
2. **Parser** = 字节 → 消息语义；不碰 socket  
3. **HEARTBEAT** = 「有飞控在说话」；还不是 Vehicle  
4. **QML 只绑定** `udpLink` / `mavlinkParser`；禁止 UI 拆帧  
5. **Application** 负责创建与接线（P6）  
6. **官方 mavlink 头**（长期、可跟 QGC）  

---

## 构建与运行

```bash
cd /Users/x_hoon/minigcs
cmake --preset macos-qt6
cmake --build --preset macos-qt6
./build/apps/minigcs/MiniQGC.app/Contents/MacOS/MiniQGC
```

自测心跳（需 pymavlink，建议 venv）：

```bash
python3 -m venv .venv && .venv/bin/pip install pymavlink
# App Link 页 → Start 后：
.venv/bin/python3 tools/send_heartbeat.py 127.0.0.1 14550 5
```

---

## 下一轮学习建议

1. 学员确认 M3 UI 看懂（Link 左右两栏）  
2. **M4**：`heartbeatReceived` → `Vehicle` 生命周期  
3. 仍 UI-first；遵守 P2（Vehicle 可空）  

---

## 最近会话

| 日期 | 内容 |
|------|------|
| 2026-07-31 | M0–M2 实现 |
| 2026-08-03 | 串口/UDP/图传概念；交接 |
| 2026-08-06 | **M3**：ADR 0001 + MavlinkParser + Link/Analyze 心跳 UI；离线 feed 自测通过 |
