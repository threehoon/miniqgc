# Coding Style — MiniQGC

> **写法**在本文；**架构金科玉律**在 [ARCHITECTURE_PATTERNS.md](ARCHITECTURE_PATTERNS.md) 与 [AGENTS.md](../AGENTS.md)。  
> 对齐 QGroundControl `CODING_STYLE.md` 的关键选择，便于二开时读/写同一套肌肉记忆。  
> **状态：M0 起强制执行。**

## 与 AGENTS 的分工

| 文档 | 管什么 |
|------|--------|
| AGENTS + ARCHITECTURE_PATTERNS | 模块、调度、Fact、Vehicle 空指针、QML 禁区 |
| **本文** | 缩进、命名、头文件、类布局、日志写法、QML 结构 |

## General

| 项 | 约定 |
|----|------|
| 缩进 | **4 空格**，禁止 Tab |
| 换行 | LF |
| 编码 | UTF-8 |
| 行宽 | **120** 列（目标；引入 clang-format 后 enforce） |
| 语言 | C++20 |
| Qt | Qt 6（Core / Gui / Qml / Quick 等按需） |
| 实现文件扩展名 | **`.cc`**（对齐 QGC，不用 `.cpp`） |
| 头文件 | **`.h`** + `#pragma once` |

## Comments

- 写 **why**（意图、权衡、不变量），不写 what  
- 公开 API 可用 `///` 简短说明  
- 模块级契约写在 `docs/modules/`，不靠注释代替  

## Naming（钉死）

| 元素 | 约定 | 示例 |
|------|------|------|
| 命名空间 | `mini::<module>` | `mini::app`、`mini::core` |
| 类 | PascalCase | `Application`、`UdpLink` |
| 方法 / 函数 | camelCase | `init()`、`startListening()` |
| 局部 / 参数 | camelCase | `activeVehicle` |
| **私有成员** | **`_leadingUnderscore`** | `_engine`、`_sysId` |
| 私有方法 | `_leadingUnderscore` + camelCase | `_loadRootQml()` |
| 常量 | PascalCase 或 UPPER_SNAKE | `MaxRetryCount` / `MAX_RETRY_COUNT` |
| 枚举 | `enum class` + PascalCase | `enum class LinkState` |
| 文件 | 与主类同名 | `Application.h` / `Application.cc` |
| CMake 目标 | `mini_<module>` | `mini_core`、`mini_app` |
| 可执行文件 | `minigcs` | |
| 日志 category 名 | `mini.<area>` | `mini.app`、`mini.comms` |
| QML id / 类型 | camelCase id / PascalCase 文件 | `id: root`、`Main.qml` |

## Headers

include 顺序（组之间空一行）：

1. 对应的模块/项目头  
2. 其它项目头  
3. Qt 头（**全路径**，如 `<QtCore/QObject>`）  
4. 标准库  

```cpp
#pragma once

#include "Logging.h"

#include <QtCore/QObject>
#include <QtCore/QString>

#include <memory>
```

### 类声明顺序

```cpp
class Application : public QGuiApplication
{
    Q_OBJECT

public:
    // 构造 / 析构
    // 公开 API

signals:
    // …

private:
    // _privateMethods
    // _members
};
```

## C++ 习惯

- 优先 `[[nodiscard]]` 标注重要返回值  
- 指针使用前判空（尤其 Vehicle / active）— 见 P2  
- **生产路径不用 `Q_ASSERT` 顶业务**；用早返回 + 日志（P8）  
- 一个主要类一对 `.h/.cc`  

## Logging

- 使用 **分类日志**：`qCDebug` / `qCWarning` / `qCCritical`  
- category 字符串：`mini.app`、`mini.core`、`mini.comms`…  
- **禁止**把无分类 `qDebug()` 当作长期正式方案  
- 声明：`Q_DECLARE_LOGGING_CATEGORY`；定义：`Q_LOGGING_CATEGORY`  

```cpp
qCWarning(MiniAppLog) << "Failed to load root QML";
```

## Qt / QML

- 状态：`Q_PROPERTY` + NOTIFY  
- 注册：`QML_ELEMENT` / `QML_SINGLETON` / `QML_UNCREATABLE`（按需）  
- **QML 禁止**解析 MAVLink、操作 socket（P4）  
- 用户可见字符串后续用 `qsTr()`（有 i18n 时）  

QML 文件建议顺序：`id` → 属性 → 信号 → 函数 → 子项 → `Connections` → `Component.onCompleted`。

## 模块与依赖

- 遵守 P5 依赖方向；新代码进正确 `src/<module>/`  
- 调度接线只在 `app`（P6）  

## Git commits

Conventional Commits：`feat` / `fix` / `docs` / `build` / `chore` / `refactor` / `test` / `ci` / `style`。

```text
feat(app): load root QML window
docs(patterns): clarify P2 null vehicle
build: add mini_core target
```

## Formatting tools

- 目标：仓库根 `.clang-format`（4 空格、ColumnLimit 120，贴近 QGC）  
- M0 已提供基础 `.clang-format`；提交前尽量格式化改动文件  

## What not to do

- 循环依赖、UI→comms 直连  
- 无文档的全局可变单例  
- 整文件复制 QGC 源码进本仓  
- 与本文冲突的「个人临时风格」合入 main  
