cmake_minimum_required(VERSION 3.16)

project(LaserCAD VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp                    header/Manager/mainwindow.ui
        src/mainwindow.cpp      header/mainwindow.h
)
include_directories(${PROJECT_SOURCE_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LaserCAD
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        # cavaliercontours
        src/cavaliercontours.cpp
        header/CavalierContours/intrcircle2circle2.hpp
        header/CavalierContours/intrlineseg2circle2.hpp
        header/CavalierContours/intrlineseg2lineseg2.hpp
        header/CavalierContours/mathutils.hpp
        header/CavalierContours/plinesegment.hpp
        header/CavalierContours/polyline.hpp
        header/CavalierContours/polylinecombine.hpp
        header/CavalierContours/polylineintersects.hpp
        header/CavalierContours/polylineoffset.hpp
        header/CavalierContours/polylineoffsetislands.hpp
        header/CavalierContours/staticspatialindex.hpp
        header/CavalierContours/vector.hpp
        header/CavalierContours/vector2.hpp
        header/CavalierContours/cavaliercontours.h
        # GraphicsView
        header/GraphicsView/graphicsview.h                    src/graphicsview.cpp
        header/GraphicsView/laseritem.h                             src/laseritem.cpp
        header/GraphicsView/polylineitem.h                       src/polylineitem.cpp
        header/GraphicsView/arcitem.h                                 src/arcitem.cpp
        header/GraphicsView/protocol.h                               src/protocol.cpp
        # TreeViewModel
        header/TreeViewModel/manager.h                            src/manager.cpp
        header/TreeViewModel/treenode.h                           src/treenode.cpp
        header/TreeViewModel/treeviewmodel.h               src/treeviewmodel.cpp
        # widget
        header/titlebar.h                                                                src/titlebar.cpp
        #utils
        header/logger.h                          src/logger.cpp
        header/utils.h                              src/utils.cpp
        header/css.h                               #[[src/css.cpp]]
        resource/button.qrc

        header/Manager/keyboardmanager.h            src/keyboardmanager.cpp
        header/Manager/scenemanager.h                    src/scenemanager.cpp
        header/Manager/uimanager.h                          src/uimanager.cpp
        header/Manager/drawmanager.h             src/drawmanager.cpp
        header/Manager/protocol1.h
        header/Manager/editmanager.h
        src/editmanager.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET LaserCAD APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(LaserCAD SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(LaserCAD
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(LaserCAD PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/TreeViewModel)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/GraphicsView)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/CavalierContours)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/Manager)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.LaserCAD)
endif()
set_target_properties(LaserCAD PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS LaserCAD
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(LaserCAD)
endif()
