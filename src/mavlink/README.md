# src/mavlink

Protocol framing: raw bytes → MAVLink messages.

| Item | Value |
|------|--------|
| CMake | `mini_mavlink` |
| Milestone | **M3** |
| Library | official `mavlink/c_library_v2` (ADR 0001) |
| Contract | [docs/modules/mavlink.md](../../docs/modules/mavlink.md) |

## Public surface (M3)

| Symbol | Role |
|--------|------|
| `MavlinkLib.h` | Include wrapper for `common/mavlink.h` |
| `MavlinkParser` | `feed(bytes)` → HEARTBEAT fields + logs |

Does **not** open sockets (comms) or create Vehicle (M4).
