add_library(mini_core STATIC
    Logging.cc
    Logging.h
)

add_library(mini::core ALIAS mini_core)

target_include_directories(mini_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mini_core
    PUBLIC
        Qt6::Core
)

target_compile_features(mini_core PUBLIC cxx_std_20)
