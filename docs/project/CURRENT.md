# CURRENT — 实现侧交接单（MiniQGC）

## 一句话状态

**M2 页面与功能已落地（Link 页 + UDP 收包）。协作方式：先出界面/效果 → 你看 → 再讲解模块。请先运行看 Link 页，看完说「看完了」再开讲。**

## 协作方式（默认）

```text
1. 导师先实现「能看见的效果」
2. 你本地运行、点一点
3. 你确认看完
4. 导师讲：页面功能、实现方式、模块职责、对照 QGC
```

## 里程碑

| ID | 状态 |
|----|------|
| M0 启动 | ✅ |
| M1 导航壳 | ✅ |
| M2 Link / UDP | ✅ 待你验收界面 |
| M3 MAVLink | ⬜ |

## 请你现在做（验收 M2 画面）

```bash
cd /Users/x_hoon/minigcs
cmake --preset macos-qt6 && cmake --build --preset macos-qt6
./build/apps/minigcs/MiniQGC.app/Contents/MacOS/MiniQGC
```

1. 默认进入 **Link** 页（顶栏第 3 个）  
2. 端口默认 **14550**，点 **Start**  
3. 另开终端：`echo hello | nc -u -w1 127.0.0.1 14550`  
4. 看日志区是否出现 RX 行；顶栏/底栏显示 UDP 状态  

看完回复：**看完了**（或说明哪里不对）。

## 最近

| 日期 | 内容 |
|------|------|
| 2026-07-31 | 约定 UI-first 学法；实现 M2 Link+UDP |
