@echo off
setlocal enabledelayedexpansion

rem 设置路径变量
set "PROJECT_TYPE = Debug"
set "BUILD_DIR=build"
set "TARGET_EXE=LaserCAD.exe"
set "DLL_PATH=lib\RTC5\RTC5DLLx64.dll"
set "OUTPUT_DIR=output"
set "QT_ENV=C:\Windows\System32\cmd.exe /A /Q /K E:\Repo\Qt\5.15.18\mingw81_32\bin\qtenv2.bat"


rem 清理output文件夹 创建一个新的
if exist "%OUTPUT_DIR%" (
    echo Removing old output folder...
    rmdir /s /q "%OUTPUT_DIR%"
)
mkdir "%OUTPUT_DIR%"

rem 查找 Release/Debug 结尾的目录
for /d %%D in (%BUILD_DIR%\*%PROJECT_TYPE%) do (
    if exist "%%D\%TARGET_EXE%" (
        echo Found: %%D\%TARGET_EXE%
        copy "%%D\%TARGET_EXE%" "%OUTPUT_DIR%\"
        goto :found_exe
    )
)

echo Can not find LaserCAD.exe in Build folder. please build the project in Qt first.
exit /b 1

:found_exe

rem 拷贝 DLL
if exist "%DLL_PATH%" (
    copy "%DLL_PATH%" "%OUTPUT_DIR%\"
) else (
    echo Can not RTC5DLLx64.dll,exit.
    exit /b 1
)

rem 打开新终端 执行 qtenv2 和 windeployqt 打包
echo open Qt pack tool windeployqt and start packing software...
start "" cmd.exe /K "cd /d %cd%\%OUTPUT_DIR% && call E:\Repo\Qt\5.15.18\mingw81_64\bin\qtenv2.bat &&  cd E:\Repo\LaserCAD_QT\output && windeployqt LaserCAD.exe"

rem 等待打包完成
echo Waiting for windeployqt to finish...
timeout /t 5 >nul

rem 拷贝 output 到 F盘
echo Copying output to F:\output ...
xcopy "%OUTPUT_DIR%" "F:\output" /E /I /Y
echo Finished copying to F:\output

rem 删除项目中output 文件夹
echo Removing local output folder...
rmdir /s /q "%OUTPUT_DIR%"


echo finish packing.
pause
