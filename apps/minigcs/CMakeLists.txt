qt_add_executable(minigcs
    main.cc
)

# QML lives under repo qml/; aliases keep module-relative names clean.
set(MINI_QML_DIR "${CMAKE_SOURCE_DIR}/qml")
set(MINI_QML_FILES
    "${MINI_QML_DIR}/Main.qml"
    "${MINI_QML_DIR}/FlyView.qml"
    "${MINI_QML_DIR}/PlanView.qml"
    "${MINI_QML_DIR}/AnalyzeView.qml"
    "${MINI_QML_DIR}/SettingsView.qml"
)

foreach(_qml_file IN LISTS MINI_QML_FILES)
    get_filename_component(_qml_name "${_qml_file}" NAME)
    set_source_files_properties("${_qml_file}" PROPERTIES
        QT_RESOURCE_ALIAS "${_qml_name}"
    )
endforeach()

qt_add_qml_module(minigcs
    URI MiniQGC
    VERSION 1.0
    QML_FILES
        ${MINI_QML_FILES}
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

if(APPLE)
    set_target_properties(minigcs PROPERTIES
        MACOSX_BUNDLE_BUNDLE_NAME "MiniQGC"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.miniqgc.app"
    )
endif()
