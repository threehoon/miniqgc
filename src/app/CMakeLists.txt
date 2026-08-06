add_library(mini_app STATIC
    Application.cc
    Application.h
)

add_library(mini::app ALIAS mini_app)

target_include_directories(mini_app
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mini_app
    PUBLIC
        mini_core
        mini_comms
        mini_mavlink
        mini_vehicle
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        Qt6::QuickControls2
)

target_compile_features(mini_app PUBLIC cxx_std_20)
