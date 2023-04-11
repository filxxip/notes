cmake_minimum_required(VERSION 3.16)

project(notesdatabaseproject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4.2 COMPONENTS Quick Core Widgets  REQUIRED)

find_package(nlohmann_json 3.7.0 REQUIRED)
find_package(CURL REQUIRED )
#target_link_libraries(appnotesdatabaseproject PRIVATE nlohmann_json::nlohmann_json)

qt_standard_project_setup()

qt_add_executable(appnotesdatabaseproject
    main.cpp
    src/gui/statuses.h
    src/gui/mycontroller.h
    src/gui/mycontroller.cpp
    src/gui/log_controller.cpp
    src/gui/log_controller.h
    src/controller/abstract_data_client.cpp
    src/controller/abstract_data_client.h
    resources/resources.qrc
)

qt_add_qml_module(appnotesdatabaseproject
    URI notesdatabaseproject
    VERSION 1.0
    QML_FILES
        Main.qml
        src/gui/EntryField.qml
        src/gui/CustomButton.qml
        src/gui/ButtonText.qml
        src/gui/LoginView.qml
        src/gui/RegisterView.qml
        src/gui/GUIConfig.qml
        src/gui/qmldir
        src/gui/TitleBox.qml
        src/gui/SwitchButton.qml
        src/gui/LoginRepeater.qml
        src/gui/CloseButton.qml

)


set_target_properties(appnotesdatabaseproject PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
)

target_include_directories(appnotesdatabaseproject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(appnotesdatabaseproject
    PRIVATE Qt6::Quick Qt6::Core Qt6::Widgets CURL::libcurl

)
