# apps/minigcs

可执行入口：`main.cc` → `mini::app::Application`。

- CMake 目标：`minigcs`（输出名 `MiniQGC`）  
- QML 模块 URI：`MiniQGC`  
- 原则：main 保持瘦；调度在 `src/app`（P6）  

