cmake_minimum_required(VERSION 3.10)

if(CMAKE_VERSION VERSION_GREATER "3.19.0")
  cmake_policy(SET CMP0112 OLD)
endif()

project(astyle CXX)

# Build Options - executable by default, libraries on request
option(BUILD_JAVA_LIBS   "Build java library"   OFF)
option(BUILD_SHARED_LIBS "Build shared library" OFF)
option(BUILD_STATIC_LIBS "Build static library" OFF)

# Release Build by default (except for Borland)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_STANDARD 17)

# Linux Soname Version
set(MAJORVER 3)
set(MINORVER 5)
set(PATCHVER 0)
set(SOLIBVER ${MAJORVER}.${MINORVER}.${PATCHVER})

# AStyle Source
file(GLOB SRCS src/*.cpp)

# AStyle Documentation, selected files
list(APPEND DOCS
    doc/astyle.html
    doc/install.html
    doc/news.html
    doc/notes.html
    doc/styles.css)

list(APPEND MAN
    man/astyle.1)

# Define java as a shared library
 if(BUILD_JAVA_LIBS)
    set(BUILD_SHARED_LIBS ON)
 endif()

 # Define the output type
 if(BUILD_SHARED_LIBS OR BUILD_STATIC_LIBS)
    add_library(astyle ${SRCS})
else()
    add_executable(astyle ${SRCS})
endif()


# compiler options:

if(APPLE)
    target_compile_options( astyle PRIVATE -W -Wall -fno-rtti -fno-exceptions -stdlib=libc++)
elseif(NOT WIN32)   # Linux
    target_compile_options(astyle PRIVATE -Wall -Wextra -fno-rtti -fno-exceptions)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "gnu")
        execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)

	elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel" AND CMAKE_BUILD_TYPE STREQUAL "Release")
        # remove intel remarks for release build
        target_compile_options(astyle PRIVATE -wd11074,11076)
    endif()
elseif(MINGW)
    target_compile_options(astyle PRIVATE -Wall -Wextra -fno-rtti -fno-exceptions)
elseif(BORLAND)     # Release must be explicitly requested for Borland
    target_compile_options(astyle PRIVATE -q -w -x-)   # Cannot use no-rtti (-RT-)
elseif(MSVC)        # Visual Studio
    target_compile_options(astyle PRIVATE /utf-8)
endif()

# Set build-specific compile options
if(BUILD_SHARED_LIBS OR BUILD_STATIC_LIBS)
    if(BUILD_JAVA_LIBS)
        find_package(JNI)
        if (NOT JNI_FOUND)
            set(err_jni "Use '-DJAVA_HOME=<JNI Directory>' to define the Java path")
            message(FATAL_ERROR ${err_jni})
        endif()
        target_compile_options(astyle PRIVATE -DASTYLE_JNI)
        target_include_directories(astyle PRIVATE ${JNI_INCLUDE_DIRS})
    else()
        target_compile_options(astyle PRIVATE -DASTYLE_LIB)
    endif()
    # Windows DLL exports removed
    set_property(TARGET astyle PROPERTY DEFINE_SYMBOL "")
    # Linux solib version added
    set_property(TARGET astyle PROPERTY VERSION ${SOLIBVER})
    set_property(TARGET astyle PROPERTY SOVERSION ${MAJORVER})
endif()


# Linker options:

# Strip release builds
if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
	if(NOT BUILD_STATIC_LIBS AND NOT BORLAND AND NOT MSVC)
		add_custom_command(TARGET astyle POST_BUILD
						   COMMAND ${CMAKE_STRIP} $<TARGET_FILE_NAME:astyle>)
	endif()
endif()
# Shared library options
if(BUILD_SHARED_LIBS)
	set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")     # remove -rdynamic
	if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Intel")
		# need static linking because cannot find the intel libraries at runtime
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-intel")
	elseif(MINGW)
		# minGW dlls don't work
		# tdm-gcc dlls work with everything except python
		set(CMAKE_SHARED_LINKER_FLAGS
			"${CMAKE_SHARED_LINKER_FLAGS} -Wl,--add-stdcall-alias -Wl,--dll")
	elseif(BORLAND)
		# use a development environment to compile Borland dlls
	endif()
endif()


# Installation options:

# Define install directories
# To uninstall 'xargs rm < install_manifest.txt'
# Default linux install prefix is /usr/local"
# This may be modified by -DCMAKE_INSTALL_PREFIX=
# Default Win32 install prefix is not used (C:/Program Files (x86))

option(INSTALL_DOC ON)

if(BUILD_SHARED_LIBS OR BUILD_STATIC_LIBS)
    if(NOT WIN32)
        install(TARGETS astyle DESTINATION lib)
    endif()
else()
    if(SKBUILD)
        install(TARGETS astyle DESTINATION "${SKBUILD_SCRIPTS_DIR}")
        if(INSTALL_DOC)
            install(FILES ${DOCS} DESTINATION "${SKBUILD_DATA_DIR}/share/doc/astyle/html")
            install(FILES ${MAN} DESTINATION "${SKBUILD_DATA_DIR}/share/man/man1")
        endif()
    elseif(WIN32)
        set(pf86 "PROGRAMFILES(x86)")
        set(prog_files $ENV{${pf86}})
        if(NOT ${prog_files})
            set(prog_files $ENV{PROGRAMFILES})
        endif()
        install(TARGETS astyle DESTINATION "${prog_files}/AStyle")
        install(FILES ${DOCS} DESTINATION "${prog_files}/AStyle/doc")
    elseif(APPLE)
        # install to the default /usr/local/bin because of SIP restrictions
        install(TARGETS astyle DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
        if(INSTALL_DOC)
            install(FILES ${DOCS} DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/astyle/html")
        endif()
    else()
        # change default to /usr/bin, the same as package installs
        if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
            set(CMAKE_INSTALL_PREFIX "/usr")
		endif()
        install(TARGETS astyle DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
        if(INSTALL_DOC)
            install(FILES ${DOCS} DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/astyle/html")
            install(FILES ${MAN} DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1")
        endif()
	endif()
endif()


# output files:

# Set output file names if different than 'astyle'
if(BUILD_JAVA_LIBS)
    if(WIN32)
        set_property(TARGET astyle PROPERTY OUTPUT_NAME AStyle32j)
        set_property(TARGET astyle PROPERTY PREFIX "")
    else()
        set_property(TARGET astyle PROPERTY OUTPUT_NAME astylej)
    endif()
elseif(BUILD_SHARED_LIBS)
    if(WIN32)
        set_property(TARGET astyle PROPERTY OUTPUT_NAME AStyle32)
        set_property(TARGET astyle PROPERTY PREFIX "")
    endif()
elseif(BUILD_STATIC_LIBS)
    if(WIN32)
        set_property(TARGET astyle PROPERTY OUTPUT_NAME AStyleLib)
        set_property(TARGET astyle PROPERTY PREFIX "")
    endif()
else()
    if(WIN32)
        set_property(TARGET astyle PROPERTY OUTPUT_NAME AStyle)
    endif()
endif()


# print info:

if(BUILD_JAVA_LIBS)
	SET(ASTYLE_BUILD_TYPE "Java Shared Library")
elseif(BUILD_SHARED_LIBS)
	SET(ASTYLE_BUILD_TYPE "Shared Library")
elseif(BUILD_STATIC_LIBS)
	SET(ASTYLE_BUILD_TYPE "Static Library")
else()
	SET(ASTYLE_BUILD_TYPE "Executable")
endif()

# Display build information

message( STATUS "---------- General Configuration ----------" )
message( STATUS )
message( STATUS "CMake Generator:       ${CMAKE_GENERATOR}" )
message( STATUS "CMake Compiler:        ${CMAKE_CXX_COMPILER_ID}" )
message( STATUS "AStyle Build:          ${ASTYLE_BUILD_TYPE}" )
message( STATUS "AStyle Configuration:  ${CMAKE_BUILD_TYPE}" )
if( BUILD_JAVA_LIBS )
    message( STATUS "Java Include Path:     ${JAVA_INCLUDE_PATH}" )
endif()
message( STATUS )
message( STATUS "-------------------------------------------" )
