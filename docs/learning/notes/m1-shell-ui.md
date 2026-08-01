# M1 — Shell UI（主窗信息架构）

## 业务

用户打开地面站后，需要在几个**顶层作业面**之间切换：

| 视图 | 用户意图（完整 GCS） | M1 做到 |
|------|----------------------|---------|
| Fly | 监视飞行、控制 | 占位页 + 可切换 |
| Plan | 编航线、上下载任务 | 占位页 + 可切换 |
| Analyze | 日志 / 消息检查 | 占位页 + 可切换 |
| Settings | 地面站自身设置 | 占位页 + 可切换 |

底栏提示：**No vehicle**（P2：无飞机是合法状态，M4 前预期如此）。

## Mini 设计

- 仅 QML 壳：`Main.qml` 顶栏导航 + `StackLayout`
- 子页：`FlyView` / `PlanView` / `AnalyzeView` / `SettingsView`
- **不改** C++ 启动链（仍 M0 的 Application）
- 遵守 P4：无协议、无 socket

简化点（相对 QGC）：

- QGC：Fly/Plan 主舞台 + toolDrawer 装 Analyze/Setup/Settings  
- Mini M1：四个顶栏 Tab，降低复杂度；以后若要对齐抽屉，可再改导航形态，不伤模块边界  

## QGC 对照

| Mini | QGC |
|------|-----|
| `qml/Main.qml` | `src/MainWindow/MainWindow.qml` |
| `FlyView.qml` | `src/FlyView/` |
| `PlanView.qml` | `src/PlanView/` |
| Analyze / Settings 顶栏 | 常经 toolDrawer / `showTool` |

## 验收

- [x] 顶栏可切换四页  
- [x] 标题/底栏反映当前视图  
- [x] 构建通过  
