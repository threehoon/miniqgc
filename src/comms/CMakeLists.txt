add_library(mini_comms STATIC
    UdpLink.cc
    UdpLink.h
)

add_library(mini::comms ALIAS mini_comms)

target_include_directories(mini_comms
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(mini_comms
    PUBLIC
        mini_core
        Qt6::Core
        Qt6::Network
)

target_compile_features(mini_comms PUBLIC cxx_std_20)
