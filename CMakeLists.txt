cmake_minimum_required(VERSION 3.16)

project(LaserCAD_Designer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp            src/mainwindow.ui
        src/mainwindow.cpp      header/mainwindow.h
        src/graphicsview.cpp    header/graphicsview.h 
)
include_directories(${PROJECT_SOURCE_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LaserCAD_Designer
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
        # GraphicsItem
        header/GraphicsItem/polylineitem.h      src/polylineitem.cpp
        header/GraphicsItem/arcitem.h               src/arcitem.cpp
        header/GraphicsItem/protocol.h              src/protocol.cpp
        # main widget
        header/manager.h                     src/manager.cpp
        header/logger.h                          src/logger.cpp
        header/titlebar.h                        src/titlebar.cpp
        # header/style.h                         src/style.cpp
        #utils
        resource/button.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET LaserCAD_Designer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(LaserCAD_Designer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(LaserCAD_Designer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(LaserCAD_Designer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(LaserCAD_Designer PRIVATE ${PROJECT_SOURCE_DIR}/header)
target_include_directories(LaserCAD_Designer PRIVATE ${PROJECT_SOURCE_DIR}/header/GraphicsItem)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.LaserCAD_Designer)
endif()
set_target_properties(LaserCAD_Designer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS LaserCAD_Designer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(LaserCAD_Designer)
endif()
