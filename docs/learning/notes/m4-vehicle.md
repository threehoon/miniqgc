# M4 — Vehicle（概念笔记）

## 策略（实现已定）

- **First-seen 单机**：第一帧 HEARTBEAT 的 sysid 建 `Vehicle`  
- 同 sysid → 更新；其它 sysid → 忽略  
- **5s** 无心跳或 **Link Stop** → 无飞机（null）  
- UI 一律判空（P2）  

## 和 M3 的分工

| 层 | 职责 |
|----|------|
| Parser | 线上刚说了什么（翻译） |
| Vehicle | 我们跟踪的那架飞机当前状态（档案） |
| Manager | 0..N 架的容器；M4 的 N≤1 |

## 代码落点

| 路径 | 角色 |
|------|------|
| `src/vehicle/Vehicle.*` | 单机对象 |
| `src/vehicle/VehicleManager.*` | activeVehicle / 超时 / first-seen |
| `src/app/Application.*` | 接线 heartbeat → manager；注入 QML |
| `qml/FlyView.qml` | 有/无飞机卡片 |
| `qml/Main.qml` | 顶栏 Vehicle chip + 底栏 statusText |

## 怎么验

```bash
# App: Link Start → 发心跳 → 顶栏 "Vehicle sys=1"，Fly 页绿色卡片
# 停发 >5s → "No vehicle"
# Link Stop → 立刻 No vehicle
```

## 以后多机

按 sysid 多实例 + 选 active；Parser 不用改。  
