# ADR 0001: Official MAVLink C headers (c_library_v2)

| 字段 | 值 |
|------|-----|
| Status | accepted |
| Date | 2026-08-06 |
| Milestone | M3 |

## Context

M3 needs bytes → MAVLink message decoding (at least HEARTBEAT).  
The library choice is hard to reverse: it shapes CMake, dialect coverage, and how closely Mini maps to QGC secondary-development work.

Constraints:

- Long-term product / architecture sandbox (not a one-off demo)
- Same mental model as QGC (`mavlink.h`, `mavlink_message_t`, `mavlink_parse_char`)
- Prefer no fragile hand-rolled frame parser

## Decision

Use the **official MAVLink C headers** from  
[`mavlink/c_library_v2`](https://github.com/mavlink/c_library_v2) (pre-generated `common` dialect).

- CMake: `FetchContent` → INTERFACE include target `mavlink_c_library_v2`
- App code includes via a thin wrapper `MavlinkLib.h` (mirrors QGC `MAVLinkLib.h` idea)
- Dialect for M3: **common** (HEARTBEAT lives there)

## Alternatives considered

1. **Hand-written HEARTBEAT-only parser** — zero deps, but wrong long-term; breaks on real SITL streams and teaches the wrong habit.
2. **Third-party high-level MAVLink SDK** — may hide wire format; diverges from QGC reading path.
3. **Generate headers at build time from mavlink XML (like QGC CPM + mavgen)** — most flexible; heavier (Python, deterministic hash patches). Deferred until we need custom dialects or QGC-synced generation.

## Consequences

**Positive**

- Wire-compatible with PX4/ArduPilot SITL and tools
- Same types/APIs students will see in QGC (`mavlink_parse_char`, `mavlink_msg_*_decode`)
- Easy to extend to more `common` messages without redesign

**Negative / follow-ups**

- FetchContent needs network on first configure (or a populated cache)
- Pin `GIT_TAG` when we care about bit-reproducible CI builds
- Later may switch to build-time mavgen if we need QGC-identical dialect pinning (superseding ADR)

## QGC mapping

| Mini | QGC |
|------|-----|
| `c_library_v2` headers | CPM `mavlink` package + generated include |
| `src/mavlink/MavlinkLib.h` | `src/MAVLink/MAVLinkLib.h` |
| `MavlinkParser` | role of `MAVLinkProtocol` (simplified) |
