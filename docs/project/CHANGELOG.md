# Changelog

本文件记录 **MiniGCS 仓库的可感知变更**（不是 Git log 的完整替代）。  
格式接近 [Keep a Changelog](https://keepachangelog.com/)，版本号在正式发版前可用里程碑标签。

## [Unreleased]

### Added

- 独立仓库初始化（`main`）
- 文档与目录框架：`AGENTS.md`、`docs/project/*`、`docs/modules/*`、`docs/learning/*`、`docs/decisions/*`
- QGC 参考路径约定：`docs/REFERENCE.md`
- 源码/测试/CMake 占位目录（无业务实现）
- 实现侧交接单 `docs/project/CURRENT.md`；默认学法「设计课 → 作业本」
- **架构金科玉律** `docs/ARCHITECTURE_PATTERNS.md`（P1–P8）与 AGENTS 短列表

### Changed

- M-doc 标为完成；进度/里程碑/AGENTS 与学法同步
- AGENTS 对齐 QGC 结构：快速链接 / 金律 / Critical / DoD

### Fixed

- （无）

---

## Template for later

```markdown
## [M0] - YYYY-MM-DD

### Added
- ...

### Changed
- ...
```
