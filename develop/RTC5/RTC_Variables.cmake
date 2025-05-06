cmake_minimum_required(VERSION 3.7)
	
set (RTC_FILES_DIR 
	"${CMAKE_CURRENT_SOURCE_DIR}/../RTC5/RTC5LIB") 

set (X86_X64 )

if ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
set (X86_X64 x64)
endif ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")

set (RTC_LIB 
${RTC_FILES_DIR}/RTC5DLL${X86_X64}.lib
)
set (RTC_DLL
${RTC_FILES_DIR}/RTC5DLL${X86_X64}.dll
)	
	
set (RTC_FILES
	${RTC_DLL}
	${RTC_FILES_DIR}/RTC5Dat.dat
	${RTC_FILES_DIR}/RTC5Out.out
	${RTC_FILES_DIR}/RTC5Rbf.rbf )
	
	
macro(set_vs_debugger_path ProjectName)
file( WRITE "${CMAKE_CURRENT_BINARY_DIR}/${ProjectName}.vcxproj.user" 
"<?xml version=\"1.0\" encoding=\"utf-8\"?>     
<Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">
    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|Win32'\">
        <LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
        <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
    </PropertyGroup>
    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|Win32'\">
        <LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
        <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
    </PropertyGroup>
	<PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">
        <LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
        <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
    </PropertyGroup>
    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">
        <LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
        <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
    </PropertyGroup>
 </Project>")
endmacro(set_vs_debugger_path)