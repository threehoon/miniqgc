# Project progress

> 新对话先读 **[CURRENT.md](CURRENT.md)**。

## Dashboard

| 项 | 值 |
|----|-----|
| **当前里程碑** | **M3 完成** → 下一轮 **M4 Vehicle** |
| **整体进度（粗估）** | ~40% |
| **最近更新** | 2026-08-06 — M3 MAVLink HEARTBEAT 解析 |
| **GitHub** | https://github.com/threehoon/miniqgc |

## Milestone board

| ID | 名称 | 状态 |
|----|------|------|
| M-doc / Patterns | 文档与 P1–P8 | **done** |
| M0 | 启动空壳 | **done** |
| M1 | Shell UI 导航 | **done** |
| M2 | UDP Link + 概念对齐 | **done** |
| M3 | MAVLink parse | **done** |
| M4 | Vehicle | todo |
| SerialLink | 串口链路 | todo（可与 M4 并行） |

## Completed

- [x] 规范、M0、M1、M2 实现  
- [x] 学员理解：Link 管道、UDP≠图传、Serial 同级  
- [x] 笔记 `docs/learning/notes/m2-link-udp.md`  
- [x] **M3**：官方 mavlink 头 + `MavlinkParser` + Link/Analyze 心跳 UI  
- [x] ADR 0001、`m3-mavlink-parse.md`  

## Next

- 学员跑通心跳 UI → 讲解收口 → **M4 Vehicle**  

