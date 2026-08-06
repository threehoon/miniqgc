cmake_minimum_required(VERSION 3.21)

project(MiniQGC
    VERSION 0.1.0
    DESCRIPTION "Mini ground control station — architecture sandbox for QGC secondary development"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Export compile_commands for clangd (optional convenience)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Network)

qt_standard_project_setup(REQUIRES 6.5)

add_subdirectory(src/core)
add_subdirectory(src/comms)
add_subdirectory(src/mavlink)
add_subdirectory(src/vehicle)
add_subdirectory(src/app)
add_subdirectory(apps/minigcs)

message(STATUS "MiniQGC ${PROJECT_VERSION} — targets: mini_core, mini_comms, mini_mavlink, mini_vehicle, mini_app, minigcs")
