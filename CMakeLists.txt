cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

project(notesdatabaseproject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b")
#add_compile_options(-std=c++2b)

message("CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")


find_package(Qt6 6.4.2 COMPONENTS Quick Core Widgets  REQUIRED)
include(FindPkgConfig)
pkg_check_modules(CURLPP REQUIRED curlpp)
find_package(nlohmann_json 3.7.0 REQUIRED)
find_package(CURL REQUIRED )
set(curlpp_DIR "/usr/include/curlpp")
#find_package(curlpp REQUIRED)
#target_link_libraries(appnotesdatabaseproject PRIVATE nlohmann_json::nlohmann_json)
#target_link_libraries(notesdatabaseproject ${CURLPP_LDFLAGS})
qt_standard_project_setup()

qt_add_executable(appnotesdatabaseproject
    main.cpp
    src/gui/statuses.h

    src/gui/notebook/categorycontroller.cpp
    src/gui/notebook/categorycontroller.h
    src/gui/notebook/texteditorcontroller.h
    src/gui/notebook/texteditorcontroller.cpp

    src/gui/maincontroller/maincontroller.cpp
    src/gui/maincontroller/maincontroller.h

    src/gui/viewcontroller/viewcontroller.cpp
    src/gui/viewcontroller/viewcontroller.h

    src/gui/customdialog/dialogcontroller.cpp
    src/gui/customdialog/dialogcontroller.h

    src/gui/models/entryfieldmodel.h
    src/gui/models/switchermodel.h
    src/gui/models/userviewlistmodel.cpp
    src/gui/models/userviewlistmodel.h
    src/gui/models/radiobuttonmodel.h

    src/gui/modelutils/adaptermodel.cpp
    src/gui/modelutils/adaptermodel.h
    src/gui/modelutils/customlistmodel.cpp
    src/gui/modelutils/customlistmodel.h
    src/gui/modelutils/listmodelbuilder.h
    src/gui/modelutils/customlistmodelregistering.h
    src/gui/modelutils/invokablelistmodel.cpp
    src/gui/modelutils/invokablelistmodel.h
    src/gui/models/calendarmodel.h

    src/gui/userview/logcontroller.cpp
    src/gui/userview/logcontroller.h
    src/gui/userview/entrycontroller.h
    src/gui/userview/entrycontroller.cpp
    src/gui/userview/userconfigcontroller.cpp
    src/gui/userview/userconfigcontroller.h

    src/gui/userview/specificcontrollers/guestcontroller.cpp
    src/gui/userview/specificcontrollers/guestcontroller.h
    src/gui/userview/specificcontrollers/logincontroller.cpp
    src/gui/userview/specificcontrollers/logincontroller.h
    src/gui/userview/specificcontrollers/registercontroller.cpp
    src/gui/userview/specificcontrollers/registercontroller.h

    src/gui/usereditview/usereditcontroller.cpp
    src/gui/usereditview/usereditcontroller.h
    src/gui/usereditview/mainusercontroller.cpp
    src/gui/usereditview/mainusercontroller.h


    src/gui/calendar/calendarcontroller.h
    src/gui/calendar/calendarcontroller.cpp

    src/gui/calendar/clockcontroller.cpp
    src/gui/calendar/clockcontroller.h

    src/gui/radiobutton/radiobuttoncontroller.cpp
    src/gui/radiobutton/radiobuttoncontroller.h

    src/gui/cpputils/utils.cpp
    src/gui/cpputils/utils.h

    src/backend/datamanager/dataclient.h

    src/backend/datamanager/filedataclient.cpp
    src/backend/datamanager/filedataclient.h
    src/backend/datamanager/filedataclientadapter.cpp
    src/backend/datamanager/filedataclientadapter.h
    src/backend/datamanager/filemanager.cpp
    src/backend/datamanager/filemanager.h
    src/backend/datamanager/pathmanager/path.cpp
    src/backend/datamanager/pathmanager/path.h
    src/backend/datamanager/serverdataclient.cpp
    src/backend/datamanager/serverdataclient.h
    src/backend/datamanager/directobjsmanagers/basicdatabasedata.cpp
    src/backend/datamanager/directobjsmanagers/basicdatabasedata.h


    src/backend/datamanager/directobjsmanagers/overallmanager.h
    src/backend/datamanager/directobjsmanagers/overallmanager.cpp

    src/backend/datamanager/directobjsmanagers/singletonobjectmanager/singletonobjectmanager.cpp
    src/backend/datamanager/directobjsmanagers/singletonobjectmanager/singletonobjectmanager.h

    src/backend/datamanager/directobjsmanagers/notes/note.h
    src/backend/datamanager/directobjsmanagers/notes/notesmanager.h
    src/backend/datamanager/directobjsmanagers/notes/notesmanager.cpp

    src/backend/datamanager/directobjsmanagers/ids/ids.h
    src/backend/datamanager/directobjsmanagers/ids/idsmanager.h
    src/backend/datamanager/directobjsmanagers/ids/idsmanager.cpp

    src/backend/datamanager/directobjsmanagers/categories/categoriesmanager.h
    src/backend/datamanager/directobjsmanagers/categories/category.h
    src/backend/datamanager/directobjsmanagers/categories/categoriesmanager.cpp

    src/backend/datamanager/directobjsmanagers/people/peoplemanager.h
    src/backend/datamanager/directobjsmanagers/people/person.h
    src/backend/datamanager/directobjsmanagers/people/peoplemanager.cpp

    src/backend/datamanager/directobjsmanagers/guidialogs/guidialogmanager.h
    src/backend/datamanager/directobjsmanagers/guidialogs/guidialog.h
    src/backend/datamanager/directobjsmanagers/guidialogs/guidialogmanager.cpp
    resources/resources.qrc
)

qt_add_qml_module(appnotesdatabaseproject
    URI notesdatabaseproject
    VERSION 1.0
    QML_FILES
        Main.qml
        src/gui/customdialog/CustomDialog.qml
        src/gui/calendar/DateChooser.qml
        src/gui/calendar/Clock.qml
        src/gui/calendar/TumblerComponent.qml

        src/gui/notebook/CategoryView.qml
        src/gui/notebook/TextEditorView.qml
        src/gui/notebook/NotebookListViewElement.qml

        src/gui/qmlutils/SwipeInComponent.qml

        src/gui/qmlutils/ButtonSwitcher.qml
        src/gui/qmlutils/ButtonText.qml
        src/gui/qmlutils/CustomButton.qml
        src/gui/qmlutils/EntryField.qml
        src/gui/qmlutils/TitleBox.qml

        src/gui/radiobutton/CustomRadioButton.qml

        src/gui/userview/ConfirmButton.qml
        src/gui/userview/LogView.qml
        src/gui/userview/LogViewEntryPart.qml

        src/gui/usereditview/UserEditView.qml
        src/gui/usereditview/EntryLabel.qml
        src/gui/usereditview/UserProfileView.qml
        src/gui/usereditview/ButtonWithImage.qml
        src/gui/usereditview/UserEditListView.qml

        src/gui/GUIConfig.qml
        src/gui/qmldir

)


set_target_properties(appnotesdatabaseproject PROPERTIES
    AUTOMOC ON
    AUTORCC ON
    AUTOUIC ON
)

target_include_directories(appnotesdatabaseproject PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
#target_link_libraries(appnotesdatabaseproject ${CURLPP_LDFLAGS})
target_link_libraries(appnotesdatabaseproject
    PRIVATE Qt6::Quick Qt6::Core Qt6::Widgets ${CURLPP_LDFLAGS}
)
