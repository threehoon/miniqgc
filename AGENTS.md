# AGENTS.md — MiniQGC

面向在本仓库工作的 **AI 编程助手** 与 **人类开发者** 的约定说明。  
结构对齐 QGroundControl 的 `AGENTS.md`：**短入口 + 金科玉律 + 链接细则**。

## 快速链接

| 文档 | 内容 |
|------|------|
| [docs/ARCHITECTURE_PATTERNS.md](docs/ARCHITECTURE_PATTERNS.md) | **架构模式展开（P1–P8）** |
| [docs/CODING_STYLE.md](docs/CODING_STYLE.md) | 命名、C++/QML、日志（细则持续补全） |
| [docs/architecture.md](docs/architecture.md) | 分层与依赖表 |
| [docs/modules/](docs/modules/) | 各模块契约 |
| [docs/project/CURRENT.md](docs/project/CURRENT.md) | **实现侧新对话交接** |
| [docs/REFERENCE.md](docs/REFERENCE.md) | QGC 路径与里程碑对照 |
| [docs/project/MILESTONES.md](docs/project/MILESTONES.md) | 里程碑验收 |

设计课（学法/画像）：`../qgc_project/docs/learning/`（尤其 `CURRENT.md`、`LEARNER_PROFILE.md`）。

---

## 项目定位

- **是什么**：结构专业、可演进的迷你地面站（MiniQGC），按竖切里程碑加功能。  
- **为什么做**：同构沙盘——内化 QGC 级框架/模块/调度纪律，服务 **客户向 QGC 二次开发**。  
- **不是什么**：完整 QGC 克隆；也不是「简单 demo 即终点」。功能可少，**架构纪律与二开映射不能弱**。  
- **主战场**：真 QGC / Custom Build；本仓每刀应能对照「QGC 改哪里」。

---

## 金科玉律（强制 — Architecture Patterns）

违反即视为未完成。完整说明、禁止项、二开映射见  
**[docs/ARCHITECTURE_PATTERNS.md](docs/ARCHITECTURE_PATTERNS.md)**。

### 对齐 QGC 的四条

1. **P1 Fact 统一值模型** — 车辆参数/可绑定值走 Fact；禁止私建参数存储作为正式方案（M6 起全面强制）。  
2. **P2 Vehicle 可空纪律** — 使用 `Vehicle*` / activeVehicle 前必须判空；无飞机是合法状态。  
3. **P3 飞控差异策略点** — 飞控相关差异走 plugin/策略接口；禁止 UI/各处散落 `if (px4)`。  
4. **P4 QML 暴露纪律** — `Q_PROPERTY` / 正确类型注册；**QML 禁止**解析 MAVLink 或直接操作 socket。  

### 本仓强化（专业交付）

5. **P5 模块边界与依赖单向** — 代码落入 `core|comms|mavlink|vehicle|facts|ui|app`；依赖  
   `apps → app → ui → vehicle/facts → comms/mavlink → core`，禁止反向。  
6. **P6 调度 / 组装层** — 创建、接线、根窗口在 `src/app`；UI 不 `new` 链路；领域不依赖 Application。  
7. **P7 二开映射与可跟版** — 里程碑须能指出 QGC 入口/扩展点；优先学 Custom/Plugin 思维，禁以整文件抄 QGC 为完成标准。  
8. **P8 防御性编码** — 生产路径用早返回 + 分类日志；不用 assert 顶业务逻辑。  

### 工作方式（与金律配套）

- **先契约后代码** — 改行为前更新 `docs/modules/*` / 模式文档（若触及）。  
- **竖切可运行** — 里程碑交付可演示链路，而非半截空壳。  
- **文档即产品** — 结束会话更新 `docs/project/CURRENT.md` 与 PROGRESS。  

---

## 关键入口（Critical — 有代码后优先读）

| 顺序 | Mini | 对照 QGC |
|------|------|----------|
| 1 | `src/app` / Application | `src/main.cc`、`QGCApplication.*` |
| 2 | `src/vehicle` / Vehicle | `src/Vehicle/Vehicle.h` |
| 3 | `src/facts` / Fact | `src/FactSystem/Fact.h` |
| 4 | 飞控策略接口 | `src/FirmwarePlugin/FirmwarePlugin.h` |
| 5 | `src/comms` | `src/Comms/` |

模块职责：[docs/modules/](docs/modules/)。

---

## 代码结构（目标）

```text
apps/minigcs/     # 可执行入口（瘦 main）
src/app/          # 调度 / 组装 / 生命周期
src/core/         # 公共基础
src/comms/        # 链路
src/mavlink/      # 协议
src/vehicle/      # 飞机对象
src/facts/        # Fact 模型
src/ui/           # C++ ↔ QML
qml/              # 界面
tests/
cmake/
docs/
```

---

## 构建与测试

> M0 落地前下列命令为 **目标形态**；实现后改成真实 preset 名称。

```bash
cmake --preset default          # 配置（待 M0）
cmake --build --preset default  # 编译
ctest --test-dir build          # 测试（有测试后）
```

- 多文件改动时增量编译，先修红再继续。  
- 与 CI 对齐后以文档中的 CI 命令为准。  

---

## Definition of Done

完成一项改动前：

1. 不违反 **金科玉律 P1–P8**（自检见 ARCHITECTURE_PATTERNS 文末清单）。  
2. 构建通过（有工程后）；相关测试通过（有测试后）。  
3. 触及的 `docs/modules/*` / CURRENT / 模式文档已更新。  
4. 若为里程碑交付：可演示 + 有 QGC 对照说明（notes 或 CURRENT）。  
5. Commit 使用 Conventional Commits（见下）。  

---

## Commit 约定

Conventional Commits，例如：

- `feat(vehicle): track heartbeat sysid`  
- `fix(app): null-check before exposing active vehicle`  
- `docs(agents): refine architecture patterns`  
- `build: add mini_core CMake target`  

类型：`feat` / `fix` / `docs` / `build` / `chore` / `refactor` / `test` / `ci` / `style`。

---

## 学员习惯与学法

1. 先 Agent/契约与边界，再写代码。  
2. 模块化与中间调度层为默认，不是可选项。  
3. 设计课在 `qgc_project`；本仓为作业本——**设计复述过关前不主动写该里程碑业务代码**（用户明确要求除外）。  
4. 实现以学员为主；避免整模块代写。  

学法全文：`../qgc_project/docs/learning/README.md`。

## 参考项目（只读）

| 项 | 值 |
|----|-----|
| 路径 | `/Users/x_hoon/qgc_project` 或相对 `../qgc_project` |
| 规则 | 不改 QGC 应用代码完成 Mini；只读对照 |

---

## 协作口令

| 口令 | 含义 |
|------|------|
| `进度` | 读两边 CURRENT |
| `问题` | `docs/project/ISSUES.md` |
| `做 Mn` | 设计过关或明确授权后推进里程碑 |
| `对照 QGC` | 映射竖切并写 notes |
| `更新进度` | CURRENT / PROGRESS / CHANGELOG |
| `复述架构` | 对照 ARCHITECTURE_PATTERNS + architecture.md |

## 当前实现策略

- **阶段**：规范层定稿中；M-doc 完成；**无业务代码直至 M0 授权**。  
- 重大依赖与模式变更 → `docs/decisions/` ADR。  

## 相关入口

- [README.md](README.md)  
- [CLAUDE.md](CLAUDE.md) → 本文件  
