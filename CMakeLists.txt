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
        main.cpp         mainwindow.ui
        mainwindow.cpp mainwindow.h
        graphicsview.h graphicsview.cpp
)
include_directories(${PROJECT_SOURCE_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LaserCAD_Designer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
	polylineitem.h polylineitem.cpp
	variantlineitem.h variantlineitem.cpp
	manager.h manager.cpp
	lib/CavalierContours/src/cavaliercontours.cpp
	lib/CavalierContours/include/cavc/intrcircle2circle2.hpp
	lib/CavalierContours/include/cavc/intrlineseg2circle2.hpp
	lib/CavalierContours/include/cavc/intrlineseg2lineseg2.hpp
	lib/CavalierContours/include/cavc/mathutils.hpp
	lib/CavalierContours/include/cavc/plinesegment.hpp
	lib/CavalierContours/include/cavc/polyline.hpp
	lib/CavalierContours/include/cavc/polylinecombine.hpp
	lib/CavalierContours/include/cavc/polylineintersects.hpp
	lib/CavalierContours/include/cavc/polylineoffset.hpp
	lib/CavalierContours/include/cavc/polylineoffsetislands.hpp
	lib/CavalierContours/include/cavc/staticspatialindex.hpp
	lib/CavalierContours/include/cavc/vector.hpp
	lib/CavalierContours/include/cavc/vector2.hpp
	lib/CavalierContours/c_api_include/cavaliercontours.h
	utils.h utils.cpp
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
