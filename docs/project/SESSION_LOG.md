# Session log

可选的会话流水。详细进度仍以 [PROGRESS.md](PROGRESS.md) 为准。

---

## 2026-07-31 — 立项：文档框架

- **目标**：新开 `/Users/x_hoon/minigcs`，不写业务代码，搭好文件与项目管理 MD
- **完成**：Git init、AGENTS/文档树、模块占位 README
- **未做**：CMake、Qt 空壳
- **下次**：用户审阅框架 → 授权后 M0

## 2026-07-31 — 学法固化与交接单

- **目标**：默认学法改为设计课 → 作业本；维护 CURRENT 方便新对话
- **完成**：CURRENT.md、AGENTS/learning/project 文档同步；M-doc 标 done
- **未做**：M0 设计课与实现
- **下次**：在 qgc_project 开 M0 设计课

## 2026-07-31 ~ 08-01 — M0 / M1 / M2 实现

- M0 启动链；M1 导航壳；M2 UdpLink + Link 页
- UI-first：先效果后讲解

## 2026-08-03 — 链路概念收口 + 新对话交接

- 讲清：串口 USB、UDP/Wi‑Fi 遥测、≠ 图传；UdpLink↔SerialLink 对照
- 文档：`m2-link-udp.md`、comms 契约、两边 CURRENT/PROGRESS
- **下次新对话**：建议 M3 MAVLink 或 SerialLink

## 2026-08-06 — M3 MAVLink 解析

- ADR 0001：官方 `mavlink/c_library_v2`
- `MavlinkParser` + Application `datagramReceived → feed`
- Link 页双栏（RX / HEARTBEAT）、Analyze 共用 parser
- 离线 feed 自测：`msgs=1 hb=1 sys=1 type=2 ap=12`
- **下次**：学员看 UI → 讲设计；然后 M4 Vehicle

## 2026-08-06 — M4 Vehicle

- 策略：first-seen 单机；5s 超时；Link Stop clear；其它 sysid 忽略
- `Vehicle` + `VehicleManager`；heartbeatReceived → handleHeartbeat
- Fly 页 / 顶栏 chip / 底栏 statusText；P2 判空
- **会话收口**：两边 CURRENT 更新；M4 commit；新对话从 M5/SerialLink 开

## 2026-08-06 — 会话结束交接

- 学员已验证 M3 HB 日志；M4 代码已落地并构建通过
- 学习记录写入 CURRENT（实现侧 + 设计课侧）
- **新对话**：复制 CURRENT 中的开场提示即可接上
