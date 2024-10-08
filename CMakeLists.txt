cmake_minimum_required(VERSION 3.5)

project(QtDrawingClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

#------------

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp mainwindow.h mainwindow.ui
        udpreciever.cpp udpreciever.h
        tablewidget.h tablewidget.cpp tablewidget.ui
        graphicswidget.h graphicswidget.cpp graphicswidget.ui
        # qcustomgraphicsitem.h qcustomgraphicsitem.cpp
        resources.qrc
)



#Flatbuffers Api autogen
set(FLATC_EXEC "${CMAKE_SOURCE_DIR}/3rd-party/flatbuffers-23.1.21/flatc")

add_custom_command(
    OUTPUT "${CMAKE_SOURCE_DIR}/api_generated.h"
    COMMAND ${FLATC_EXEC} --cpp --gen-object-api -o "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/Server/api.fbs"
    DEPENDS "${CMAKE_SOURCE_DIR}/Server/api.fbs"
    COMMENT "Генерация API для FlatBuffers"
)

#

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtDrawingClient
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QtDrawingClient APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QtDrawingClient SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QtDrawingClient
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(QtDrawingClient PRIVATE "3rd-party/flatbuffers-23.1.21/include")

target_link_libraries(QtDrawingClient PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(QtDrawingClient PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QtDrawingClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtDrawingClient)
endif()

add_custom_target(apigen DEPENDS "${CMAKE_SOURCE_DIR}/api_generated.h")
add_dependencies(QtDrawingClient apigen)

