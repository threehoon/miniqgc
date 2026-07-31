# MiniGCS

可扩展的迷你地面站（Mini Ground Control Station）。

- **工程目标**：按专业开发流程搭建可长期演进的 GCS 骨架（CMake、模块边界、文档、Git）。
- **学习目标**：对照 [QGroundControl](https://github.com/mavlink/qgroundcontrol) 同构学习架构与领域，**不追求功能完整对齐**。
- **当前阶段**：**仅文档与目录框架**（尚无业务代码）。

## 仓库关系

| 仓库 | 路径 | 角色 |
|------|------|------|
| **本仓 MiniGCS** | `/Users/x_hoon/minigcs` | 主开发：实现、进度、问题、决策 |
| **参考 QGC** | `/Users/x_hoon/qgc_project`（相对路径 `../qgc_project`） | 只读对照：业务与架构标准答案 |

详见 [docs/REFERENCE.md](docs/REFERENCE.md)。

## 文档地图（用 Markdown 管项目）

| 文档 | 作用 |
|------|------|
| [AGENTS.md](AGENTS.md) | AI / 开发者总约定（入口） |
| [docs/architecture.md](docs/architecture.md) | 分层、模块、依赖方向 |
| [docs/CODING_STYLE.md](docs/CODING_STYLE.md) | 代码与命名约定 |
| [docs/REFERENCE.md](docs/REFERENCE.md) | QGC 参考路径与里程碑对照 |
| [docs/project/README.md](docs/project/README.md) | 项目管理总览 |
| [docs/project/MILESTONES.md](docs/project/MILESTONES.md) | 里程碑定义（M0…） |
| [docs/project/PROGRESS.md](docs/project/PROGRESS.md) | **项目进度仪表盘**（唯一权威） |
| [docs/project/ISSUES.md](docs/project/ISSUES.md) | 问题 / 风险 / 待决事项 |
| [docs/project/CHANGELOG.md](docs/project/CHANGELOG.md) | 变更记录 |
| [docs/modules/README.md](docs/modules/README.md) | 模块职责与接口定义索引 |
| [docs/decisions/README.md](docs/decisions/README.md) | 架构决策记录（ADR） |
| [docs/learning/README.md](docs/learning/README.md) | 对照 QGC 的学习体系 |

## 计划目录结构（代码将落在这些位置）

```text
minigcs/
├── AGENTS.md / CLAUDE.md / README.md
├── apps/minigcs/          # 可执行入口（尚未实现）
├── src/
│   ├── app/               # Application 生命周期
│   ├── core/              # 公共类型、日志门面
│   ├── comms/             # 链路抽象
│   ├── mavlink/           # 协议解析
│   ├── vehicle/           # 飞机对象
│   ├── facts/             # 参数/遥测统一模型
│   └── ui/                # C++ ↔ QML 桥接
├── qml/                   # QML 界面
├── tests/                 # 测试
├── cmake/                 # CMake 辅助
└── docs/                  # 项目文档（当前已就绪）
```

## 当前状态

- [x] 独立 Git 仓库
- [x] 文档与目录框架
- [ ] CMake / Qt 工程可配置
- [ ] M0 空壳可运行

进度以 [docs/project/PROGRESS.md](docs/project/PROGRESS.md) 为准。

## 构建（占位）

业务代码落地后，预期流程：

```bash
cmake --preset default   # 待添加
cmake --build build
```

在实现 M0 前请勿依赖上述命令。

## License

待定（与学习/个人项目用途对齐后再定）。
