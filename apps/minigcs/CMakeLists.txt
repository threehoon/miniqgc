qt_add_executable(minigcs
    main.cc
)

# Keep sources under repo qml/; alias so the module sees "Main.qml".
set(MINI_MAIN_QML "${CMAKE_SOURCE_DIR}/qml/Main.qml")
set_source_files_properties("${MINI_MAIN_QML}" PROPERTIES
    QT_RESOURCE_ALIAS "Main.qml"
)

qt_add_qml_module(minigcs
    URI MiniQGC
    VERSION 1.0
    QML_FILES
        "${MINI_MAIN_QML}"
)

set_target_properties(minigcs PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    OUTPUT_NAME "MiniQGC"
)

target_link_libraries(minigcs
    PRIVATE
        mini_app
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        Qt6::QuickControls2
)

# macOS: put next to other tooling expectations
if(APPLE)
    set_target_properties(minigcs PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "MiniQGC"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.miniqgc.app"
    )
endif()
