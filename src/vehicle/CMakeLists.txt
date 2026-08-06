add_library(mini_vehicle STATIC
    Vehicle.cc
    Vehicle.h
    VehicleManager.cc
    VehicleManager.h
)

add_library(mini::vehicle ALIAS mini_vehicle)

target_include_directories(mini_vehicle
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mini_vehicle
    PUBLIC
        mini_core
        Qt6::Core
)

target_compile_features(mini_vehicle PUBLIC cxx_std_20)
