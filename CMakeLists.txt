cmake_minimum_required(VERSION 3.16)

project(notesdatabaseproject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appnotesdatabaseproject
    main.cpp
)

qt_add_qml_module(appnotesdatabaseproject
    URI notesdatabaseproject
    VERSION 1.0
    QML_FILES Main.qml
)

set_target_properties(appnotesdatabaseproject PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appnotesdatabaseproject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(appnotesdatabaseproject
    PRIVATE Qt6::Quick
)

install(TARGETS appnotesdatabaseproject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
