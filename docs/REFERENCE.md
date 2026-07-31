# Reference: QGroundControl

MiniGCS uses QGC as a **read-only reference** for architecture and domain behavior.

## Paths

| Kind | Path |
|------|------|
| Absolute | `/Users/x_hoon/qgc_project` |
| Relative (from MiniGCS root) | `../qgc_project` |

Machine-specific overrides (optional, gitignored): copy ideas into `docs/REFERENCE.local.md` if you move the trees.

## Rules

1. **Do not modify** QGC production/application code for MiniGCS features.
2. **Do not vendor** large QGC source trees into MiniGCS.
3. When a milestone is done, update the mapping table below and learning notes under `docs/learning/`.
4. Prefer opening the **smallest file list** that explains one vertical slice.

## QGC learning assets (existing)

If you already studied QGC in-tree:

- `../qgc_project/docs/learning/` — prior study plan & notes
- `../qgc_project/AGENTS.md` — QGC agent golden rules
- `../qgc_project/docs/en/qgc-dev-guide/` — official dev guide

Mini-side learning progress: [learning/](learning/).

## Milestone ↔ QGC entry points

| Mini milestone | Intent | QGC starting points (relative to QGC root) |
|----------------|--------|-----------------------------------------------|
| **M0** Scaffold build | App starts | `src/main.cc`, `src/QGCApplication.*`, root `CMakeLists.txt` |
| **M1** Shell UI | Window + page switch | `src/MainWindow/MainWindow.qml`, `src/FlyView/`, `src/PlanView/` |
| **M2** Link bytes | UDP/serial IO | `src/Comms/` (`LinkManager`, `UDPLink`, `SerialLink`, …) |
| **M3** MAVLink parse | HEARTBEAT etc. | `src/MAVLink/`, message handling near vehicle |
| **M4** Vehicle object | One vehicle exists | `src/Vehicle/Vehicle.*`, multi-vehicle manager |
| **M5** Bind UI | Show mode/connected | Fly view QML + vehicle properties |
| **M6** Facts (lite) | Telemetry/params model | `src/FactSystem/` |
| **M7+** Missions / cmds | As planned | `src/MissionManager/`, command paths on `Vehicle` |

Refine file lists in each milestone note under `docs/learning/notes/` when implementing.

## Architecture ideas to steal (not code)

| Idea | Why Mini cares |
|------|----------------|
| Fact system | Single path for parameters/telemetry values |
| FirmwarePlugin | Later: don’t scatter `if (px4)` |
| Multi-vehicle null checks | Safe lifecycle habits |
| Link abstraction | Swap UDP/serial without rewriting vehicle |
| Custom / plugin boundary | Future branding without forking core |

## Suggested read order for agents

1. This file  
2. [architecture.md](architecture.md)  
3. [project/MILESTONES.md](project/MILESTONES.md)  
4. Only then open QGC files for the **current** milestone  
