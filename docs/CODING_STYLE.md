# Coding Style — MiniGCS

> Applies once application code exists. Aligned in spirit with QGC / modern Qt C++20, simplified for a small team of one + AI.

## Language & toolchain

- C++20
- Qt 6 (Core, Gui, Qml, Quick; others as needed)
- CMake 3.21+ (target-based, presets)
- Formatting: clang-format (config TBD at M0)

## Naming

| Kind | Convention | Example |
|------|------------|---------|
| Namespaces | `mini::module` | `mini::comms` |
| Classes | PascalCase | `UdpLink`, `Vehicle` |
| Methods / functions | camelCase | `startListening()` |
| Members | `_camelCase` or trailing `_` (pick one at M0 and stick) | `_sysId` |
| Files | Match class: `UdpLink.h` / `UdpLink.cc` | |
| CMake targets | `mini_<module>` | `mini_comms` |
| QML types | PascalCase | `VehicleSummary.qml` |

## Headers & modules

- One primary class per pair of `.h` / `.cc` when practical.
- Public headers expose stable API only; put helpers in `detail/` or `.cc`.
- Prefer forward declarations in headers.

## Qt / QML

- Expose state with `Q_PROPERTY` and notify signals.
- Register types deliberately (`QML_ELEMENT` / singleton pattern as needed).
- No MAVLink or socket logic in QML.

## Error handling

- Prefer explicit failure paths (return `bool` + log, `std::optional`, or result type) over assert-only design.
- Log with categorized loggers: `mini.comms`, `mini.vehicle`, etc.

## Comments

- Prefer clear names over long comments.
- Comment *why* and invariants, not *what* the next line does.
- Module-level contracts live in `docs/modules/*.md`, not only in code.

## Git commits

Conventional Commits:

```text
feat(vehicle): track heartbeat sysid
fix(comms): reconnect UDP on bind failure
docs(project): update PROGRESS for M0
build: add mini_core CMake target
chore: gitignore build trees
```

## What not to do

- Circular module dependencies
- Global mutable singletons without a documented owner
- Copying large QGC files wholesale into this repo
