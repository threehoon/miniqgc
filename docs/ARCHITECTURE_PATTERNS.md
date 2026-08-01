# Architecture Patterns — MiniQGC 架构金科玉律（展开版）

> **权威细则**在本文；**短列表**在根目录 [AGENTS.md](../AGENTS.md)。  
> 结构对齐 QGroundControl 的 Architecture Patterns（Fact / Multi-Vehicle / FirmwarePlugin / QML），并增加本仓专业交付所需条目。  
> 状态：规范定稿（实现前）；代码落地后若修订须走 ADR + 更新 AGENTS。

---

## 为何需要「模式」而不只是目录名

客户向 QGC 二次开发时，最贵的错误不是「少写一个功能」，而是：

- 旁路 Fact 私建参数存储  
- 不判空 `activeVehicle` 导致现场崩溃  
- 飞控差异散落 `if (px4)` 无法跟版  
- UI 直接碰协议/链路  

Mini 功能可以少，**这些判断肌肉必须练对**。下列模式是强制纪律，不是建议。

---

## 与 QGC 四条的对照总表

| # | QGC 模式 | Mini 模式（本仓名） | 同构点 | Mini 阶段差异 |
|---|----------|---------------------|--------|----------------|
| P1 | Fact System | **Fact 统一值模型** | 值/参数走 Fact，禁私建存储 | M6 起强制；M6 前禁止「临时 Map 当永久方案」写进主干 |
| P2 | Multi-Vehicle | **Vehicle 可空与多机纪律** | 用前判空 | M4 起有 Vehicle；此前 UI 也不得假设「一定有飞机」 |
| P3 | Firmware Plugin | **飞控差异策略点** | 差异集中、禁散落 if | M7+ 或有第二飞控前可只有接口占位；**禁止**在 UI/comms 写死飞控名分支蔓延 |
| P4 | QML Integration | **QML 暴露纪律** | property / 注册宏 / UI 不碰协议 | M0 起：根窗可极简；有领域对象后严格 property |
| P5 | （QGC 隐含分层） | **模块边界与依赖单向** | 领域分包 | 全阶段强制 |
| P6 | （QGC Application/Managers） | **调度 / 组装层** | 组装与接线集中 | 全阶段强制；默认 `src/app` |
| P7 | Custom / 少改主干思想 | **二开映射与可跟版** | 扩展优先于乱改内核 | 学法与交付目标强制 |
| P8 | 防御性编码 | **生产路径不用 assert 顶逻辑** | 早返回 + 日志 | 全阶段强制 |

---

## P1 — Fact 统一值模型（对齐 QGC Fact System）

### 规则

1. 飞控参数、需要绑定到 UI 的遥测/设置值，**必须**进入 Fact（或 FactGroup）管道。  
2. **禁止**为车辆参数再造第二套存储（如全局 `QMap` + 手写同步）作为正式方案。  
3. UI **只绑** Fact / 门面属性，不在 QML 里维护「真源」副本。  

### 禁止

- Setup/调参页自己 `sendMavlink` 读写参数并本地 `property` 当唯一真相  
- 同一参数在 C++ 与 QML 各存一份且无单一写入路径  

### 允许的过渡（须在 ISSUES/笔记标明）

- M6 之前：可用只读展示字段做竖切演示，但 **不得** 扩散成参数子系统；M6 必须收敛到 Fact。  

### 二开映射（真 QGC）

- 入口：`src/FactSystem/Fact.h`、ParameterManager、Setup 相关  
- 客户加参/调参页 → Fact，不要旁路  

### 违反后果

无法做单位/元数据/多飞控参数页统一；客户版与上游 QGC 习惯断裂。

---

## P2 — Vehicle 可空与多机纪律（对齐 QGC Multi-Vehicle）

### 规则

1. 任何 `Vehicle*` / `activeVehicle()` / QML `activeVehicle` **使用前必须判空**。  
2. **无飞机是合法状态**（未连接、断开中、切换中）。  
3. 不得在对象构造时缓存 activeVehicle 指针并假定长期有效（应随 active 变化更新或每次取用并判空）。  
4. 设计上预留多机：即使 M4 先做单机，API 也避免「全局唯一 Vehicle 单例且不可空」的死形状（可用 Manager 持有 0..N 架）。  

### 禁止

- `vehicle->foo()` 无守卫  
- UI 假定启动即有飞机  

### 二开映射

- `MultiVehicleManager::activeVehicle()`、QML `QGroundControl.multiVehicleManager.activeVehicle`  
- 客户现场「没连上就点按钮」是常态  

### 违反后果

随机崩溃；多机/断线场景无法交付。

---

## P3 — 飞控差异策略点（对齐 QGC Firmware Plugin）

### 规则

1. 飞控栈差异（模式名、能力位、特殊命令、参数名差异等）**集中**在策略/插件点，不得在 UI、comms、随机工具函数里复制粘贴分支。  
2. 调用方通过 **Vehicle 上的 plugin/策略接口** 询问能力，而不是 `if (autopilot == PX4)` 散落各处。  
3. 在引入第二固件或厂商固件前，至少保留 **接口边界**（即使只有一个 `GenericFirmwarePolicy` 实现）。  

### 禁止

- Fly/QML 里大量 `isPx4` / `isArduPilot`  
- 在 `comms` 层根据飞控类型改包解析哲学（协议解析保持通用；差异在更高策略）  

### 二开映射

- `FirmwarePlugin.h`、`vehicle->firmwarePlugin()`  
- 客户指定单一飞控或魔改固件 → 扩 Plugin，少改主干  

### 违反后果

多客户/多飞控时无法维护；跟版冲突爆炸。

---

## P4 — QML 暴露纪律（对齐 QGC QML Integration）

### 规则

1. 需要绑定的状态用 `Q_PROPERTY` + 变更通知；需要调用的用 `Q_INVOKABLE` / slots，并有明确归属对象。  
2. 使用 Qt6 注册方式（`QML_ELEMENT` / `QML_SINGLETON` / `QML_UNCREATABLE` 等），**禁止**无文档的野路子全局指针乱塞（若用 root context 注入，须在 app 调度层单点完成并写进模块契约）。  
3. **QML 禁止**：解析 MAVLink、直接操作 socket、拥有链路生命周期。  
4. 领域对象（如 Vehicle）默认 **C++ 创建**；QML 不可随意 `new` 破坏不变量（对齐 `QML_UNCREATABLE` 思想）。  

### 禁止

- 在 `.qml` 里实现协议状态机  
- UI 模块链接并调用 `comms` 私有实现  

### 二开映射

- 定制仪表/品牌页：绑 Vehicle/Fact property  
- Custom 换皮：资源与 Plugin，而不是复制协议栈到 QML  

---

## P5 — 模块边界与依赖单向（本仓强化）

### 规则

1. 新代码必须落入明确模块：`core` / `comms` / `mavlink` / `vehicle` / `facts` / `ui` / `app` / `apps`。  
2. 依赖只允许向下（见 [architecture.md](architecture.md)）：

   ```text
   apps → app → (ui) → vehicle / facts → comms / mavlink → core
   ```

3. 每个模块的「负责 / 不负责」以 [docs/modules/](modules/) 为准；变更契约先改文档再改代码。  
4. CMake 上按模块目标链接，禁止「所有 .cc 编进一个无边界大杂烩」作为长期形态。  

### 禁止

- `comms` 依赖 `ui` 或 `vehicle` 反向依赖 `app`  
- 在 `core` 引入业务协议  

### 二开映射

- 改 QGC 时先归 `src/Comms` vs `Vehicle` vs `FlyView`  
- 客户需求先归域再动刀  

---

## P6 — 调度 / 组装层（本仓强化，对齐你的中间层习惯）

### 规则

1. **组装根**在 `src/app`（`Application` 或等价物）：创建模块实例、信号槽接线、加载根 QML、管理生命周期。  
2. UI 只面对调度层暴露的门面 / 领域公开 API，**不**自己 `new UdpLink`。  
3. 领域模块 **不**依赖调度层类型（禁止 `vehicle` include `Application.h` 回调生命周期）。  
4. 接线膨胀时，可 ADR 抽出 `Coordinator`，仍属 app 侧，不把调度逻辑塞进 QML。  

### M0 形态

- `Application` = 生命周期 + 加载 QML（调度点占住）  
- 尚无 Link/Vehicle 可接时，不编造空忙总线  

### 二开映射

- 理解 `QGCApplication` + Manager 组装  
- 定制全局服务挂在启动链/组装点，而不是散落 static  

---

## P7 — 二开映射与可跟版（交付目标）

### 规则

1. 本仓每完成一个里程碑，须能回答：**同等能力在 QGC 的入口文件/扩展点是什么**（写入 learning notes 或 CURRENT）。  
2. 思考客户需求时默认顺序：

   ```text
   Custom Build / 资源覆盖 / Plugin / 配置
     → 再考虑改 QGC 核心
   ```

3. Mini 实现选择应偏向 **可迁移到 QGC 的结构**，而不是「只有沙盘能跑的奇技淫巧」。  
4. 禁止把「抄一大段 QGC 源码进 Mini」当作完成标准；要对齐的是 **边界与数据流**。  

### 二开映射

- `custom-example/`、`QGCCorePlugin`、官方 custom build 文档  

---

## P8 — 防御性编码与可观测性

### 规则

1. 生产路径用早返回 + 分类日志，**不用** `Q_ASSERT` / 裸 assert 作为唯一业务守卫（对齐 QGC）。  
2. 日志带 category（如 `mini.app`、`mini.comms`），禁止长期依赖无分类 `qDebug` 作为正式方案。  
3. 错误可定位：连接失败、解析失败、无 vehicle 等应有明确日志或 UI 状态，而不是静默失败。  

---

## Critical Modules / 关键入口（对齐 AGENTS「Critical Files」）

实现逐步长出后，下列为 **优先阅读入口**（有代码后补真实路径）：

| 优先级 | 模块 / 类型 | 对应 QGC | 何时必读 |
|--------|-------------|----------|----------|
| 1 | `app` / Application | `QGCApplication`、`main.cc` | M0+ |
| 2 | `vehicle` / Vehicle | `Vehicle.h` | M4+ |
| 3 | `facts` / Fact | `Fact.h` | M6+ |
| 4 | 飞控策略接口 | `FirmwarePlugin.h` | 引入差异时 |
| 5 | `comms` / Link | `Comms/*` | M2+ |

契约文档：[modules/](modules/)。

---

## 自检清单（改代码前后）

- [ ] 新代码落在正确模块？依赖方向是否被破坏？  
- [ ] 是否出现 UI→协议/socket？  
- [ ] Vehicle/active 是否可能为空且已处理？  
- [ ] 参数/可绑值是否走向 Fact（或已登记的过渡例外）？  
- [ ] 飞控差异是否集中而非散落？  
- [ ] 创建与接线是否在 app 调度层？  
- [ ] 能否一句话说清 QGC 对照入口？  
- [ ] 模块契约 / CURRENT 是否需要更新？  

---

## 修订流程

1. 提议变更模式 → 写 ADR（`docs/decisions/`）  
2. 改本文 + AGENTS 短列表  
3. 若已有代码，列迁移任务，禁止静默破坏  

**维护者：** 项目所有者 + 协助的 AI 须同时遵守；违反模式的 PR/改动视为未完成。
