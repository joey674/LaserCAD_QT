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
        src/main.cpp                    header/Ui/mainwindow.ui
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
        # MagicEnum
        header/MagicEnum/magic_enum.hpp
        header/MagicEnum/magic_enum_all.hpp
        header/MagicEnum/magic_enum_containers.hpp
        header/MagicEnum/magic_enum_flags.hpp
        header/MagicEnum/magic_enum_format.hpp
        header/MagicEnum/magic_enum_fuse.hpp
        header/MagicEnum/magic_enum_iostream.hpp
        header/MagicEnum/magic_enum_switch.hpp
        header/MagicEnum/magic_enum_utility.hpp
        # GraphicsView
        header/GraphicsView/graphicsview.h                     src/graphicsview.cpp
        header/GraphicsView/graphicsitem.h                      src/graphicsitem.cpp
        header/GraphicsView/polylineitem.h                       src/polylineitem.cpp
        header/GraphicsView/arcitem.h                                 src/arcitem.cpp
        header/GraphicsView/graphicsmath.h                     src/graphicsmath.cpp
        # TreeViewModel
        header/TreeViewModel/treenode.h                           src/treenode.cpp
        header/TreeViewModel/treemodel.h                        src/treemodel.cpp
        header/TreeViewModel/treeview.h                            src/treeview.cpp
        # TableViewModel
        header/TableViewModel/tablemodel.h                     src/tablemodel.cpp
        # Utils
        header/Utils/logger.h                                                      src/logger.cpp
        header/Utils/utils.hpp                                                     src/utils.cpp
        header/Utils/titlebar.h                                                    src/titlebar.cpp
        resource/button.qrc
        # Ui
        header/Ui/uimanager.h                                                   src/uimanager.cpp
        header/Ui//css.h
        # Keyboard
        header/Keyboard/keyboardmanager.h                   src/keyboardmanager.cpp
        # Scene
        header/Scene/scenemanager.h                                 src/scenemanager.cpp
        header/Scene/drawmanager.h                                   src/drawmanager.cpp
        header/Scene/editmanager.h                                      src/editmanager.cpp
        # main
        header/manager.h                                                            src/manager.cpp
        header/protocol.h
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
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/Scene)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/Ui)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/Keyboard)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/MagicEnum)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/Utils)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/TableViewModel)

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
