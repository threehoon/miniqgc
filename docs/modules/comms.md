# comms

| 字段 | 值 |
|------|-----|
| Source | `src/comms/` |
| CMake target | `mini_comms` |
| Milestone | **M2**（UDP 已交付；Serial 未做） |
| Patterns | P5、P6（由 app 创建）、P4（QML 只绑定） |

## Responsibility

- **链路（Link）字节 IO**：打开/关闭通道、收（及将来发）原始字节  
- 当前实现：`UdpLink`（UDP 监听与收包日志）  
- 规划：`SerialLink`（串口设备 + 波特率），与 UdpLink **同级**  
- 向 UI 暴露状态；向后续模块提供原始数据信号（供 M3 解析）  

## Non-goals

- MAVLink 解析（→ `mavlink` / M3）  
- 创建 Vehicle（→ `vehicle` / M4）  
- 图传视频（→ 将来 Video，与遥测 Link 分离）  

## 概念：Link 不是「飞机已连接」

- `start()` = 打开管道（bind 端口 / open 串口）  
- 无对端数据时仍可 `running == true`  
- 业务意义上的「有飞机」要等心跳解析 + Vehicle（M3/M4）  

## 介质对照

| | UDP（已有） | Serial（规划） |
|--|-------------|----------------|
| 场景 | SITL、Wi‑Fi/网络遥测、网关 | USB 直连、数传在电脑侧呈串口 |
| 配置 | `localPort` | `portName` + `baudRate` |
| 打开 | bind | open 设备 |
| 数据 | datagram + 对端地址 | 字节流 |

详见笔记：[../learning/notes/m2-link-udp.md](../learning/notes/m2-link-udp.md)。

## Public API (M2 已实现)

| 符号 | 说明 |
|------|------|
| `mini::comms::UdpLink` | QObject：`start`/`stop`/`clearLog`；属性见头文件 |
| Context property | `udpLink`（`Application` 注入） |
| 信号 `datagramReceived` | 原始包，供 M3 |

## Public API (规划 SerialLink)

| 概念 | 与 UdpLink 对齐 |
|------|-----------------|
| `start`/`stop`/`running` | 同 |
| `portName`/`baudRate` | 替代 `localPort` |
| 统计/日志/错误 | 同模式 |
| 字节到达信号 | 同层出口给解析器 |

## Depends on

- `mini_core`  
- Qt Network（UDP）；将来 Serial 需 Qt SerialPort  
- **不得**依赖 `ui` / QML；**不得**依赖 `vehicle`  

## QGC counterparts

- `src/Comms/UDPLink`、`SerialLink`、`LinkManager`、`LinkInterface`  

## Changelog

- M2：`UdpLink` + Link 页 + 文档说明 Serial 对照  
