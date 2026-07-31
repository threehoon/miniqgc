# AGENTS.md — MiniGCS

Instructions for AI coding agents and human developers working on **MiniGCS**.

## Project identity

- **What**: A small, professionally structured ground control station that grows by vertical slices.
- **Why**: Learn QGroundControl’s architecture by building a parallel, minimal system with real engineering discipline (CMake, modules, docs, Git).
- **Not**: A feature-complete QGC clone. Prefer structure and correct boundaries over feature parity.

## Reference project (read-only)

| Item | Value |
|------|--------|
| Absolute path | `/Users/x_hoon/qgc_project` |
| Relative path (from this repo) | `../qgc_project` |
| Role | Architecture & domain reference only |
| Rules | **Do not modify** QGC application code for Mini work. Read, compare, take notes here. |

Details and milestone mapping: [docs/REFERENCE.md](docs/REFERENCE.md).

## Golden rules

1. **Module boundaries** — Put new code in the owning module (`comms`, `vehicle`, …). No “misc” dumping ground.
2. **Dependency direction** (strict):

   ```text
   apps → app/ui → vehicle/facts → comms/mavlink → core
   ```

   UI must not parse MAVLink. Comms must not depend on QML.
3. **Vertical slices** — Each milestone delivers a runnable chain, not a half-finished layer cake.
4. **Docs are part of the product** — Progress, issues, and module contracts live under `docs/`. Update them when behavior changes.
5. **Compare, don’t copy** — After implementing a slice, document how QGC does the same job (files + why more complex).
6. **No production `Q_ASSERT` culture** — Prefer defensive checks and clear error paths (aligned with QGC agent rules).
7. **Null vehicle discipline** — Any active/selected vehicle pointer is checked before use (learn Multi-Vehicle habits early).

## Documentation authority

| Concern | Authoritative file |
|---------|-------------------|
| Project progress | [docs/project/PROGRESS.md](docs/project/PROGRESS.md) |
| Open issues / risks | [docs/project/ISSUES.md](docs/project/ISSUES.md) |
| Milestone definitions | [docs/project/MILESTONES.md](docs/project/MILESTONES.md) |
| Module contracts | [docs/modules/](docs/modules/) |
| Architecture | [docs/architecture.md](docs/architecture.md) |
| Coding style | [docs/CODING_STYLE.md](docs/CODING_STYLE.md) |
| QGC mapping | [docs/REFERENCE.md](docs/REFERENCE.md) |
| Learning notes | [docs/learning/](docs/learning/) |
| Design decisions | [docs/decisions/](docs/decisions/) |

When finishing a session: update **PROGRESS** and **ISSUES** if anything changed.

## Collaboration commands (optional)

| Phrase | Meaning |
|--------|---------|
| `进度` | Summarize from `docs/project/PROGRESS.md` |
| `问题` | Review `docs/project/ISSUES.md` |
| `做 Mn` | Work on milestone n per `MILESTONES.md` |
| `对照 QGC` | Map current slice to `../qgc_project` and update learning notes |
| `更新进度` | Write session results into PROGRESS / CHANGELOG |
| `复述架构` | Learner restates layering; correct against `architecture.md` |

## Implementation policy

- **Current phase**: documentation & directory scaffold only — **no application code until the user asks**.
- Prefer small commits with Conventional Commits: `feat`, `fix`, `docs`, `build`, `chore`, `refactor`, `test`.
- Do not invent large dependencies without an ADR in `docs/decisions/`.
- Match style in [docs/CODING_STYLE.md](docs/CODING_STYLE.md) once code exists.

## Related entry points

- Human overview: [README.md](README.md)
- Claude / similar: [CLAUDE.md](CLAUDE.md) → this file
