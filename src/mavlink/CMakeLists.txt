# Official pre-generated MAVLink C headers (ADR 0001).
include(FetchContent)

set(MINI_MAVLINK_GIT_TAG "master" CACHE STRING "Git tag/branch for mavlink/c_library_v2")

FetchContent_Declare(
    mavlink_c_library_v2
    GIT_REPOSITORY https://github.com/mavlink/c_library_v2.git
    GIT_TAG        ${MINI_MAVLINK_GIT_TAG}
    GIT_SHALLOW    TRUE
)

FetchContent_GetProperties(mavlink_c_library_v2)
if(NOT mavlink_c_library_v2_POPULATED)
    message(STATUS "MiniQGC: Fetching mavlink/c_library_v2 (${MINI_MAVLINK_GIT_TAG})")
    FetchContent_Populate(mavlink_c_library_v2)
endif()

add_library(mavlink_c_library_v2 INTERFACE)
add_library(mini::mavlink_headers ALIAS mavlink_c_library_v2)
target_include_directories(mavlink_c_library_v2
    INTERFACE
        ${mavlink_c_library_v2_SOURCE_DIR}
)

add_library(mini_mavlink STATIC
    MavlinkParser.cc
    MavlinkParser.h
    MavlinkLib.h
)

add_library(mini::mavlink ALIAS mini_mavlink)

target_include_directories(mini_mavlink
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mini_mavlink
    PUBLIC
        mini_core
        Qt6::Core
    PRIVATE
        mavlink_c_library_v2
)

target_compile_features(mini_mavlink PUBLIC cxx_std_20)
