# Architecture — MiniGCS

> Status: **target architecture** (scaffold phase; no runtime code yet).  
> Changes that affect layering require an ADR in [decisions/](decisions/).

## Goals

1. Same *mental model* as a real GCS (link → vehicle → facts → UI).
2. Strict module boundaries so features can be added for years.
3. Small enough to understand end-to-end in one sitting per slice.

## Logical layers

```text
┌─────────────────────────────────────────┐
│  qml/  +  src/ui   (presentation)       │
├─────────────────────────────────────────┤
│  src/app           ★ 调度 / 组装根        │
│  (lifecycle, wiring, coordination)      │
├─────────────────────────────────────────┤
│  src/vehicle  │  src/facts              │
├─────────────────────────────────────────┤
│  src/comms    │  src/mavlink            │
├─────────────────────────────────────────┤
│  src/core      (types, logging, util)   │
└─────────────────────────────────────────┘
```

### 调度层（与学员既有 Qt 习惯对齐）

本项目承认 **中间调度层** 的必要性：UI 与底层链路/协议之间不直连。

| 阶段 | 形态 |
|------|------|
| M0 | `Application` = 生命周期 + 组装根（先占住调度点） |
| M2+ | 在 `app` 内创建并接线 Link / Parser / Vehicle；向 UI 只暴露门面 |
| 接线膨胀后 | 可 ADR 抽出 `Coordinator` / 注册表，仍放在 app 侧，领域模块不依赖它 |

规则：调度可依赖领域；领域与 UI 不得反向依赖调度去抢生命周期。

## Dependency rules

| Module | May depend on | Must not depend on |
|--------|---------------|--------------------|
| `core` | STL / Qt Core only (minimal) | everything else |
| `comms` | `core` | `vehicle`, `ui`, `qml` |
| `mavlink` | `core` | `ui`, `qml` |
| `vehicle` | `core`, `comms`, `mavlink` | `qml` |
| `facts` | `core` (+ later `vehicle` as needed) | `qml` parse paths |
| `ui` | app-facing models, `vehicle`, `facts` | raw sockets |
| `app` | all modules (composition root) | — |
| `apps/minigcs` | `app` only | deep internals |

## Planned runtime flow (M2–M5 sketch)

```text
UDP/Serial bytes
  → comms::Link
  → mavlink::Parser
  → vehicle::Vehicle / MultiVehicle
  → facts (telemetry values)
  → ui/qml binding
```

## Threading (intent)

| Concern | Intent |
|---------|--------|
| UI | Qt main/GUI thread only for QML and model updates |
| IO | Link read/write off GUI thread; marshal into vehicle/facts via queued signals/slots |
| Rule | Never block GUI on socket reads |

Exact design locked in an ADR when implementing M2.

## Extension model (later)

- Prefer **new module or clear interface** over growing god-objects.
- Optional CMake options (e.g. `MINI_ENABLE_SERIAL`) for incomplete features.
- Long-term: plugin-style extension points inspired by QGC `QGCCorePlugin` — not before core slices work.

## Mapping to QGC

See [REFERENCE.md](REFERENCE.md). Mini intentionally collapses many QGC classes into fewer types per milestone.
