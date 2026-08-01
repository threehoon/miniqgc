# MiniQGC

可扩展的迷你地面站（**Mini Ground Control Station**）。

用专业工程方式从零搭建一套「能长期加功能」的 GCS 骨架，并对照 [QGroundControl](https://github.com/mavlink/qgroundcontrol) 学习其架构与领域模型。

**最终目标**：具备面向客户的 **QGC 二次开发**能力（可维护、可跟版），不是停留在简单 demo。  
**本仓角色**：同构沙盘——功能体量小于 QGC，但模块边界、调度层、工程纪律按专业项目来；每刀都映射回真 QGC 的扩展点。

| 项 | 说明 |
|----|------|
| 语言 / 栈 | C++20 · Qt 6 · QML · CMake |
| 协议 | MAVLink（规划中） |
| 当前阶段 | **M0 空壳可运行**（Application 调度根 + 主窗） |
| 架构纪律 | [docs/ARCHITECTURE_PATTERNS.md](docs/ARCHITECTURE_PATTERNS.md)（P1–P8） |
| Agent 入口 | [AGENTS.md](AGENTS.md) |
| 仓库 | [github.com/threehoon/miniqgc](https://github.com/threehoon/miniqgc) |
| 许可 | [MIT](LICENSE) |

---

## 默认学法

```text
设计课（qgc_project）→ 复述过关 → 本仓自己实现 → 对照收口
```

新对话先读：**[docs/project/CURRENT.md](docs/project/CURRENT.md)**。

## 构建与运行

依赖：CMake ≥ 3.21、Ninja、Qt 6.5+（Core Gui Qml Quick QuickControls2）。

```bash
# 本机已装 Qt 时，指定前缀或使用 macos-qt6 preset（按路径改 CMakePresets.json）
cmake --preset macos-qt6
cmake --build --preset macos-qt6

# macOS
open build/apps/minigcs/MiniQGC.app
# 或
./build/apps/minigcs/MiniQGC.app/Contents/MacOS/MiniQGC
```

其它机器：设置 `CMAKE_PREFIX_PATH` 指向 Qt，再 `cmake --preset default`。

## 架构纪律（摘要）

| ID | 规则 |
|----|------|
| P1 | Fact 统一值模型 |
| P2 | Vehicle 使用前判空 |
| P3 | 飞控差异走策略点 |
| P4 | QML 不碰协议/socket |
| P5 | 模块依赖单向 |
| P6 | 调度组装在 `app` |
| P7 | 二开映射 / 可跟版 |
| P8 | 防御性编码 + 分类日志 |

全文：[docs/ARCHITECTURE_PATTERNS.md](docs/ARCHITECTURE_PATTERNS.md)。

## 仓库结构

```text
apps/minigcs/     # main + 可执行目标
src/app/          # Application 调度根（P6）
src/core/         # 日志等基础
src/comms|mavlink|vehicle|facts|ui/  # 后续里程碑
qml/Main.qml      # M0 空壳
docs/             # 模式、风格、进度、模块契约
```

## 文档导航

| 你想… | 去这里 |
|--------|--------|
| 现在做到哪 | [docs/project/CURRENT.md](docs/project/CURRENT.md) |
| 架构金律 | [docs/ARCHITECTURE_PATTERNS.md](docs/ARCHITECTURE_PATTERNS.md) |
| 代码风格 | [docs/CODING_STYLE.md](docs/CODING_STYLE.md) |
| 里程碑 | [docs/project/MILESTONES.md](docs/project/MILESTONES.md) |
| 对照 QGC | [docs/REFERENCE.md](docs/REFERENCE.md) |

## License

[MIT License](LICENSE) © 2026 threehoon.
