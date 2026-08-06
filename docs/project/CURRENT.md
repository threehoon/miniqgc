# CURRENT — 实现侧交接单（MiniQGC）

> **新开对话请先读本文件**，再读「必读文档」。  
> 本会话（2026-08-06）在此收口；下一刀从 **M5** 或 SerialLink 开始。

---

## 一句话状态

**M0–M4 已完成并已 commit：启动壳 → 导航 → UdpLink → MAVLink HEARTBEAT 解析 → Vehicle（first-seen 单机）。**  
学员已跑通心跳日志；M4 策略与可空纪律已对齐。下一轮：**M5 UI 绑定加深**（推荐）或 SerialLink / 回传。

---

## 新对话必读（按序）

| 顺序 | 文件 | 内容 |
|------|------|------|
| 1 | **本文件** | 进度与下一步 |
| 2 | [../learning/notes/m4-vehicle.md](../learning/notes/m4-vehicle.md) | Vehicle / P2 / first-seen |
| 3 | [../learning/notes/m3-mavlink-parse.md](../learning/notes/m3-mavlink-parse.md) | Parser / 官方库 |
| 4 | [../learning/notes/m2-link-udp.md](../learning/notes/m2-link-udp.md) | Link 管道 |
| 5 | [../ARCHITECTURE_PATTERNS.md](../ARCHITECTURE_PATTERNS.md) | P1–P8，尤其 P2/P4/P6 |
| 6 | 设计课 CURRENT | `/Users/x_hoon/qgc_project/docs/learning/CURRENT.md` |

---

## 双仓

| 角色 | 路径 |
|------|------|
| 实现仓 | `/Users/x_hoon/minigcs` · https://github.com/threehoon/miniqgc |
| 参考 QGC | `/Users/x_hoon/qgc_project`（只读） |
| 设计课 | `qgc_project/docs/learning/` |

---

## 里程碑看板

| ID | 内容 | 状态 | 关键 commit（本机） |
|----|------|------|---------------------|
| M0–M2 | 启动 / 壳 / UdpLink | ✅ | 历史 |
| M3 | MAVLink HEARTBEAT | ✅ | `f10dda9` |
| M4 | Vehicle + Manager | ✅ | 本收口提交 |
| M5 | UI 绑定加深 | ⬜ **建议下一轮** |
| — | SerialLink / 发指令 | ⬜ |

---

## 学员已建立的心智（勿回退）

1. **Link** = 字节管道；Start ≠ 有飞机  
2. **MAVLink** = 行业标准协议；官方库拆帧；Parser 只翻译  
3. **HEARTBEAT** = 飞控自我介绍字段（sys/type/autopilot/…）  
4. **Vehicle** = 跟踪中的飞机对象；**可空是合法状态（P2）**  
5. **M4 策略**：first-seen 单机；同 sysid 更新；其它 sysid 忽略；**5s** 无 HB 或 **Link Stop** → clear  
6. **多机预留**：按 sysid 分桶 + activeVehicle；现在 N≤1  
7. QML 只绑定，不解析、不 new 服务（P4/P6）  

---

## 协作方式（默认）

```text
① 先做出能看见的效果
② 学员本地运行、点过
③ 学员说「看完了」
④ 再讲：功能 → 实现 → 模块 → 对照 QGC
```

目标：服务 **QGC 客户向二次开发**，不是 demo 玩具。

---

## 构建与验证

```bash
cd /Users/x_hoon/minigcs
cmake --preset macos-qt6 && cmake --build --preset macos-qt6
./build/apps/minigcs/MiniQGC.app/Contents/MacOS/MiniQGC

# Link 页 Start →
# .venv/bin/python3 tools/send_heartbeat.py 127.0.0.1 14550 5
# 期望：Link 右侧 HB 日志；顶栏/Fly「Vehicle sys=1」；停发 5s → No vehicle
```

---

## 下一轮建议（给新对话 AI）

1. 读本 CURRENT + m4/m3 笔记  
2. 与学员确认：**M5**（Fly/状态绑定加深）或 SerialLink  
3. 仍 UI-first；遵守 P2 判空、P4/P6  
4. 不要默认整模块代写；先对齐范围  

### 可复制开场提示

```text
请先读：
1) /Users/x_hoon/minigcs/docs/project/CURRENT.md
2) /Users/x_hoon/minigcs/docs/learning/notes/m4-vehicle.md
3) /Users/x_hoon/minigcs/docs/learning/notes/m3-mavlink-parse.md
4) /Users/x_hoon/qgc_project/docs/learning/CURRENT.md
5) /Users/x_hoon/minigcs/AGENTS.md
按 UI-first + 设计课/作业本学法继续。M0–M4 已完成。建议 M5 或 SerialLink。
不要默认整模块代写；先对齐下一刀范围。
```

---

## 最近会话

| 日期 | 内容 |
|------|------|
| 2026-07-31 | M0–M2 |
| 2026-08-03 | 串口/UDP/图传概念交接 |
| 2026-08-06 | **M3** 实现+验证；**M4** 设计共识+实现；本会话收口备新对话 |
