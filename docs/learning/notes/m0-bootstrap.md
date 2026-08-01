# M0 — 启动骨架对照

## Mini 设计

| 职责 | 落点 |
|------|------|
| 进程入口（瘦） | `apps/minigcs/main.cc` |
| 调度 / 组装根 P6 | `src/app/Application` |
| 日志 P8 | `src/core/Logging.*` → `mini.app` / `mini.core` |
| 根 UI P4 | `qml/Main.qml`，经 `loadFromModule("MiniQGC","Main")` |
| 构建 | `mini_core` → `mini_app` → `minigcs` |

启动链：

```text
main
  → Application(argc, argv)
  → init() → _loadRootQml() → loadFromModule
  → exec()
  → shutdown()
```

## QGC 对照

| Mini | QGC |
|------|-----|
| `main.cc` | `src/main.cc` |
| `Application` | `QGCApplication` + 大量 manager 组装 |
| 分类日志 | `QGCLoggingCategory` / LogManager |
| 根 QML | `createRootWindow` / MainWindow.qml |

QGC 更复杂的原因（简）：命令行模式、多平台 Platform、Plugin 换根窗、子系统海量 init、测试/boot 模式。

## 验收

- [x] 构建成功  
- [x] 主窗加载（offscreen 日志 `root UI ready`）  
