# M3 — MAVLink 解析（概念笔记）

> 实现已落地。看完 Link 页心跳 UI 后，用本文 + `docs/project/CURRENT.md` 收口。

## 1. M3 做什么 / 不做什么

| 做 | 不做 |
|----|------|
| 把链路字节 **拆成 MAVLink 消息** | 打开 socket（M2 Link） |
| 至少解码 **HEARTBEAT** 字段 | 创建 Vehicle（M4） |
| UI 上看到 sysid/type/autopilot 等 | 完整 dialect / 任务协议 |
| 官方 C 头（`c_library_v2`） | 手写拆帧玩具解析 |

**Start 链路 ≠ 有飞机。**  
**解析到 HEARTBEAT = 线上有飞控在说话**；还不是业务上的 Vehicle 对象。

## 2. 在竖切里的位置

```text
飞控/SITL
   │  字节
   ▼
Link（UdpLink）              ← M2
   │  datagramReceived
   ▼
MavlinkParser::feed          ← M3 ★
   │  heartbeatReceived
   ▼
Vehicle（将来）              ← M4
   ▼
UI 绑定                      ← M5
```

## 3. 设计要点（为什么这样拆）

1. **Parser 不依赖 comms**：只吃 `QByteArray` → 将来 SerialLink 同一入口。  
2. **QML 不解析（P4）**：界面只绑 `mavlinkParser.*`。  
3. **Application 接线（P6）**：`datagramReceived → feed`，UI 不 `new` 解析器。  
4. **官方头（ADR 0001）**：与 QGC / 真机 / SITL 同协议栈，长期可扩消息。

## 4. 代码落点（Mini）

| 路径 | 角色 |
|------|------|
| `src/mavlink/MavlinkParser.*` | 流式解析 + HEARTBEAT 属性/日志 |
| `src/mavlink/MavlinkLib.h` | 引入 `common/mavlink.h` |
| `src/app/Application.*` | 创建 parser，接线，注入 `mavlinkParser` |
| `qml/LinkView.qml` | 左：原始 RX；右：HEARTBEAT |
| `qml/AnalyzeView.qml` | 协议视角（同一 parser） |
| `docs/decisions/0001-…` | 库选择 ADR |
| `tools/send_heartbeat.py` | 无 SITL 时发测试心跳 |

## 5. QGC 对照

| Mini | QGC |
|------|-----|
| `c_library_v2` | CPM 生成的 mavlink 头 |
| `MavlinkLib.h` | `src/MAVLink/MAVLinkLib.h` |
| `MavlinkParser` | `MAVLinkProtocol`（简化） |
| `heartbeatReceived` | `messageReceived` → Vehicle 处理 |

## 6. 本地怎么验

```bash
cd /Users/x_hoon/minigcs
cmake --preset macos-qt6 && cmake --build --preset macos-qt6
./build/apps/minigcs/MiniQGC.app/Contents/MacOS/MiniQGC
# Link 页 → Start
# 另开终端：
python3 -m venv .venv && .venv/bin/pip install pymavlink
.venv/bin/python3 tools/send_heartbeat.py 127.0.0.1 14550 5
# 右侧应出现 HB sys=… type=… autopilot=…
# 或接 PX4/ArduPilot SITL 默认 UDP 14550
```

普通 `echo hello | nc -u` 仍只在左侧 RX；右侧不应涨 HEARTBEAT。

## 7. 下一里程碑

- **M4**：`heartbeatReceived` → 创建/更新 `Vehicle`  
- SerialLink 可与 M4 并行或紧随  
