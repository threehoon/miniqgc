# MiniQGC

可扩展的迷你地面站（**Mini Ground Control Station**）。

用专业工程方式从零搭建一套「能长期加功能」的 GCS 骨架，并对照 [QGroundControl](https://github.com/mavlink/qgroundcontrol) 学习其架构与领域模型。  
**目标是学透设计、练会交付；不是做一个功能完整的 QGC 克隆。**

| 项 | 说明 |
|----|------|
| 语言 / 栈 | C++20 · Qt 6 · QML · CMake（规划中） |
| 协议 | MAVLink（规划中） |
| 当前阶段 | 文档与目录框架已就绪，**业务代码尚未开始** |
| 仓库 | [github.com/threehoon/miniqgc](https://github.com/threehoon/miniqgc) |
| 许可 | [MIT](LICENSE) |

---

## 为什么做这个项目

阅读大型开源地面站很容易「看过就忘」。本项目采用另一条路径：

```text
业务理解 → 自己竖切实现 → 对照 QGC 同切面 → 记下差异与原因 → 再加下一刀
```

工程纪律不缩水（模块边界、文档、Git、里程碑验收），功能体量刻意保持很小，确保每一阶段都能跑通、能复述、能对照。

## 设计原则

1. **竖切交付** — 每个里程碑是一条可演示的业务链，而不是半截分层空壳  
2. **模块边界清晰** — 依赖单向：`ui → vehicle/facts → comms/mavlink → core`  
3. **文档即资产** — 进度、问题、模块契约、架构决策都用 Markdown 维护  
4. **对照不抄袭** — 参考 QGC 的分层与数据流，不整文件搬迁其源码  
5. **可演进** — 目录与 CMake 目标按可扩展产品设计，避免做成一次性 demo  

## 里程碑路线（简表）

| 阶段 | 内容 | 状态 |
|------|------|------|
| **M-doc** | 仓库、Agent 约定、项目管理文档、目录骨架 | 进行中 |
| **M0** | CMake + Qt 空壳可启动 | 未开始 |
| **M1** | 主窗与页面切换（Shell UI） | 未开始 |
| **M2** | 通信链路（UDP 字节收发） | 未开始 |
| **M3** | MAVLink 解析（至少 HEARTBEAT） | 未开始 |
| **M4** | Vehicle 对象与生命周期 | 未开始 |
| **M5** | 界面绑定连接状态 / 基础遥测 | 未开始 |
| **M6** | 极简 Fact 模型 | 未开始 |
| **M7+** | 任务、命令、多机等按需扩展 | 未开始 |

完整验收标准见 [docs/project/MILESTONES.md](docs/project/MILESTONES.md)。  
**进度以 [docs/project/PROGRESS.md](docs/project/PROGRESS.md) 为准。**

## 架构一览（目标形态）

```text
┌─────────────────────────────────────┐
│  qml/  +  src/ui     展示层          │
├─────────────────────────────────────┤
│  src/app             启动与组装      │
├─────────────────────────────────────┤
│  vehicle  │  facts   领域模型        │
├─────────────────────────────────────┤
│  comms    │  mavlink 链路与协议      │
├─────────────────────────────────────┤
│  core                公共基础        │
└─────────────────────────────────────┘
```

更细的依赖规则与线程约定：[docs/architecture.md](docs/architecture.md)。

## 仓库结构

```text
miniqgc/
├── AGENTS.md              # AI / 开发者总约定
├── apps/minigcs/          # 可执行入口（待 M0）
├── src/
│   ├── app/               # Application 生命周期
│   ├── core/              # 公共类型、日志
│   ├── comms/             # 链路抽象
│   ├── mavlink/           # 协议解析
│   ├── vehicle/           # 飞机对象
│   ├── facts/             # 参数 / 遥测统一模型
│   └── ui/                # C++ ↔ QML 桥接
├── qml/                   # 界面
├── tests/                 # 测试
├── cmake/                 # CMake 辅助
└── docs/                  # 架构 · 进度 · 模块 · 学习 · 决策
```

## 文档导航

| 你想… | 去这里 |
|--------|--------|
| 看现在做到哪 | [docs/project/PROGRESS.md](docs/project/PROGRESS.md) |
| 看里程碑怎么验收 | [docs/project/MILESTONES.md](docs/project/MILESTONES.md) |
| 记问题 / 风险 | [docs/project/ISSUES.md](docs/project/ISSUES.md) |
| 查模块职责 | [docs/modules/](docs/modules/) |
| 理解分层架构 | [docs/architecture.md](docs/architecture.md) |
| 对照 QGroundControl | [docs/REFERENCE.md](docs/REFERENCE.md) |
| 写学习笔记 | [docs/learning/](docs/learning/) |
| 记录架构决策 | [docs/decisions/](docs/decisions/) |
| 给 AI 助手的规则 | [AGENTS.md](AGENTS.md) |

项目管理总览：[docs/project/README.md](docs/project/README.md)。

## 与 QGroundControl 的关系

| | MiniQGC（本仓） | QGroundControl |
|--|-----------------|----------------|
| 角色 | 主开发与交付 | **只读**参考实现 |
| 体量 | 最小可演进竖切 | 完整产品 |
| 用法 | 实现、提交、记进度 | 带读源码、对照差异 |

本地若将 QGC 克隆放在与本仓同级目录，相对路径一般为 `../qgroundcontrol` 或你的实际目录名；本机绝对路径请写在 **不提交** 的 `docs/REFERENCE.local.md`（见 `.gitignore`）。  
对照表与里程碑映射：[docs/REFERENCE.md](docs/REFERENCE.md)。

## 构建（尚未就绪）

M0 完成后预期流程类似：

```bash
cmake --preset default
cmake --build --preset default
# 启动方式将在 M0 文档中写明
```

在 M0 合并前，请勿依赖上述命令。

## 开发约定（摘要）

- 提交信息使用 [Conventional Commits](https://www.conventionalcommits.org/)（`feat` / `fix` / `docs` / `build` / `chore` …）  
- 新功能先归模块，再改代码；依赖不得反向  
- 每个里程碑更新 `PROGRESS`、必要时更新 `ISSUES` 与对照笔记  
- 编码风格见 [docs/CODING_STYLE.md](docs/CODING_STYLE.md)（代码落地后强制）

## License

本项目采用 [MIT License](LICENSE) © 2026 threehoon。
