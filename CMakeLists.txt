cmake_minimum_required(VERSION 3.5)

project(twitch_app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS QuickControls2 REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS MultimediaWidgets REQUIRED)
find_package(Qt6 COMPONENTS Multimedia REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        widgets/mainwindow.cpp
        widgets/mainwindow.h
        widgets/mainwindow.ui
        widgets/secondwidget.h
        widgets/secondwidget.cpp
        twitch/channel.h
        twitch/channel.cpp
        twitch/user.h
        twitch/user.cpp
        # htmldelegate.h
        # htmldelegate.cpp
        rest/rest.h
        rest/rest.cpp
        widgets/sidebar.h
        widgets/sidebar.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(twitch_app
        resources.qrc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET twitch_app APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(twitch_app SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(twitch_app
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(twitch_app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(twitch_app PRIVATE Qt${QT_VERSION_MAJOR}::QuickControls2)
target_link_libraries(twitch_app PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(twitch_app PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(twitch_app PRIVATE Qt${QT_VERSION_MAJOR}::MultimediaWidgets)
target_link_libraries(twitch_app PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)

set_target_properties(twitch_app PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(twitch_app)
endif()
