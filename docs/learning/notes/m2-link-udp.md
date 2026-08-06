# M2 — Link / UDP 与串口对照（概念笔记）

> 学员已理解大意。新对话可从本文 + `docs/project/CURRENT.md` 接上。

## 1. M2 做什么 / 不做什么

| 做 | 不做 |
|----|------|
| 打开一条 **收字节通道**（当前 UDP） | 解析 MAVLink（M3） |
| UI 上 Start/Stop、收包日志 | 创建 Vehicle（M4） |
| 证明「有包进地面站」 | 图传视频 |

**不是**「默认飞机已连接」。Start = 打开管道；无对端数据时链路开着也可以一直空。

## 2. 链路在地面站中的位置

```text
飞控/仿真
   │  字节（常为 MAVLink）
   ▼
Link（Serial 或 UDP 或 …）   ← M2 在这里
   ▼
MAVLink 解析                 ← M3
   ▼
Vehicle                      ← M4
   ▼
UI（Fly 等）                 ← M1 壳 + 以后绑定
```

图传（视频）通常是 **另一条路径**（Video），不要和遥测 Link 混为一谈。

## 3. 串口 vs UDP（学员已对齐的理解）

| | 串口 Serial | UDP |
|--|-------------|-----|
| 常见物理形态 | USB 直连飞控；数传在电脑侧也常变成串口 | Wi‑Fi/网络遥测；**本机 SITL 仿真**；网关转 UDP |
| 打开动作 | 打开设备名 + 波特率 | 绑定本机端口（如 14550） |
| 数据形态 | 连续字节流 | 数据报（带对端 IP:port） |
| 传的内容 | 多为 MAVLink 遥测/指令 | 同左（不是默认等于图传） |

**Wi‑Fi + UDP 发遥测**：是 UDP 的重要真实场景之一，但 UDP **不限于** Wi‑Fi。  
**图传**：可能也用 UDP/RTSP，但是 **Video 业务线**，与 M2 `UdpLink` 职责不同。

## 4. UdpLink（已实现）↔ SerialLink（未实现，同级）

| 职责 | `UdpLink`（现有） | `SerialLink`（将来） |
|------|-------------------|----------------------|
| 配置 | `localPort` | `portName` + `baudRate` |
| 打开 | `start()` → bind | `start()` → open 串口 |
| 关闭 | `stop()` | `stop()` |
| 状态 | `running` / `statusText` | 同概念 |
| 统计/日志 | packets/bytes/`logLines`/`lastError` | 同概念 |
| 数据出口 | `datagramReceived(data, host, port)` | 字节到达信号（流式，无包边界） |
| Qt 底层 | `QUdpSocket` | `QSerialPort` |
| 谁创建 | `Application`（P6） | 同样 |
| QML | context `udpLink`，`LinkView` 只绑定 | 将来 `serialLink` 或统一 `activeLink` |

上层（解析/Vehicle）应只依赖「链路能收发字节」，不写死介质。

## 5. 代码落点（Mini）

| 路径 | 角色 |
|------|------|
| `src/comms/UdpLink.*` | UDP 链路实现 |
| `src/app/Application.*` | 创建 `UdpLink`，注入 QML `udpLink` |
| `qml/LinkView.qml` | 连接页 UI |
| `qml/Main.qml` | 顶栏 **Link** + 状态条 |
| `docs/modules/comms.md` | 模块契约 |

## 6. QGC 对照

| Mini | QGC |
|------|-----|
| `UdpLink` | `src/Comms/UDPLink`（及同类） |
| 将来 `SerialLink` | `src/Comms/SerialLink` |
| 多链路管理（未做） | `LinkManager` |
| Application 接线 | 连接配置 + 链路创建路径 |

## 7. 为何 M2 先 UDP 后串口

1. 无真机也可用 `nc`/SITL 验证  
2. 串口权限/驱动易卡环境  
3. **Link 抽象相同**，串口是同模块另一种实现  
4. 服务后续二开：客户现场串口与网络都常见  

## 8. 本地怎么验

```bash
cd /Users/x_hoon/minigcs
cmake --preset macos-qt6 && cmake --build --preset macos-qt6
./build/apps/minigcs/MiniQGC.app/Contents/MacOS/MiniQGC
# Link 页 → Start → 
# echo hello | nc -u -w1 127.0.0.1 14550
```

## 9. 下一里程碑建议

- **M3**：MAVLink 解析（至少 HEARTBEAT），两种 Link 共用解析入口  
- 或补 **SerialLink** UI + 实现（真机路径）  
优先建议 M3，让「字节 → 语义」闭环；串口可并行或紧随其后。  
