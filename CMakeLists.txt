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
        src/main.cpp
        src/mainwindow.cpp      header/mainwindow.h
        # GraphicsView
        header/GraphicsView/graphicsview.h                     src/graphicsview.cpp
        header/GraphicsView/graphicsitem.h                     src/graphicsitem.cpp
        header/GraphicsView/polylineitem.h                       src/polylineitem.cpp
        header/GraphicsView/arcitem.h                                src/arcitem.cpp
        header/GraphicsView/lineitem.h                                src/lineitem.cpp
        header/GraphicsView/pointitem.h                             src/pointitem.cpp
        header/GraphicsView/circleitem.h                            src/circleitem.cpp
        header/GraphicsView/rectitem.h                                src/rectitem.cpp
        header/GraphicsView/ellipseitem.h                          src/ellipseitem.cpp
        header/GraphicsView/spiralitem.h                            src/spiralitem.cpp
        header/GraphicsView/polygonitem.h                       src/polygonitem.cpp
        header/GraphicsView/editrect.h                                src/editrect.cpp# editrect
        # TreeViewModel
        header/TreeViewModel/treenode.h                           src/treenode.cpp
        header/TreeViewModel/treemodel.h                        src/treemodel.cpp
        header/TreeViewModel/treeview.h                            src/treeview.cpp
        header/TreeViewModel/colordelegate.h                src/colordelegate.cpp
        # TableViewModel
        header/TableViewModel/tablemodel.h                   src/tablemodel.cpp
        # TabWidget
        header/TabWidget/tabwidget.h                                 src/tabwidget.cpp
        # Utils
        header/Utils/logger.h                                                      src/logger.cpp
        header/Utils/utils.hpp                                                     src/utils.cpp
        header/Utils/titlebar.h                                                    src/titlebar.cpp
        resource/resource.qrc
        # Ui
        header/uimanager.h                                                        src/uimanager.cpp
        header/Ui/css.h
        # Keyboard
        header/Keyboard/keyboardmanager.h                    src/keyboardmanager.cpp
        # LaserWorker
        header/LaserWorker/laserworker.h                          header/LaserWorker/laserworker.cpp
        header/LaserWorker/laserdeviceprotocol.h
        header/LaserWorker/threadsafequeue.h                src/threadsafequeue.cpp
        header/LaserWorker/laserdevice.h                           src/laserdevice.cpp
        header/LaserWorker/laserdevicertc5.h                   header/LaserWorker/laserdevicertc5.cpp
        header/LaserWorker/laserdevicetest.h                   header/LaserWorker/laserdevicetest.cpp
        # main
        header/manager.h                                                            src/manager.cpp
        header/protocol.h
        header/editcontroller.h                                                   src/editcontroller.cpp
        header/scenecontroller.h                                               src/scenecontroller.cpp
        header/drawcontroller.h                                                 src/drawcontroller.cpp
        header/GraphicsView/combineditem.h                  src/combineditem.cpp
        header/projectmanager.h                                             src/projectmanager.cpp
        src/css.cpp
)
set(RTC4_SOURCES
    lib/RTC4/RTC4expl.h            lib/RTC4/RTC4expl.cpp
)
set(RTC5_SOURCES
    lib/RTC5/RTC5expl.h           #[[lib/RTC5/RTC5expl.c]] lib/RTC5/RTC5expl.cpp
    lib/RTC5/RTC5explTest.h    lib/RTC5/RTC5explTest.c
)
set(RTC6_SOURCES
)
set (CAVC_SOURCES
  lib/CavalierContours/cavaliercontours.cpp
  lib/CavalierContours/intrcircle2circle2.hpp
  lib/CavalierContours/intrlineseg2circle2.hpp
  lib/CavalierContours/intrlineseg2lineseg2.hpp
  lib/CavalierContours/mathutils.hpp
  lib/CavalierContours/plinesegment.hpp
  lib/CavalierContours/polyline.hpp
  lib/CavalierContours/polylinecombine.hpp
  lib/CavalierContours/polylineintersects.hpp
  lib/CavalierContours/polylineoffset.hpp
  lib/CavalierContours/polylineoffsetislands.hpp
  lib/CavalierContours/staticspatialindex.hpp
  lib/CavalierContours/vector.hpp
  lib/CavalierContours/vector2.hpp
  lib/CavalierContours/cavaliercontours.h
)

include_directories(${PROJECT_SOURCE_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LaserCAD
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${RTC4_SOURCES}
        ${RTC5_SOURCES}
        ${RTC6_SOURCES}
        ${CAVC_SOURCES}
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
            ${RTC5_SOURCES}
            ${CAVC_SOURCES}
        )
    endif()
endif()

target_link_libraries(LaserCAD PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/TreeViewModel)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/GraphicsView)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/Ui)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/Keyboard)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/Utils)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/TableViewModel)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/TabWidget)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/header/LaserWorker)

target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/lib/CavalierContours)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/lib/RTC4)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/lib/RTC5)
target_include_directories(LaserCAD PRIVATE ${PROJECT_SOURCE_DIR}/lib/RTC6)

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

add_custom_command(TARGET LaserCAD POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${PROJECT_SOURCE_DIR}/lib/RTC5/RTC5DLLx64.dll
            $<TARGET_FILE_DIR:LaserCAD>)
