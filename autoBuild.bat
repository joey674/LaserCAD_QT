@echo off
setlocal enabledelayedexpansion

rem 设置部署类型
set "PROJECT_TYPE = Debug"  
@REM set "PROJECT_TYPE = Release"

rem 设置路径变量
set "BUILD_DIR=build"
set "TARGET_EXE=LaserCAD.exe"
@REM set "DLL_PATH=lib\RTC5\RTC5DLLx64.dll"
set "DLL_PATH=lib\RTC5\RTC5DLL.dll"
set "OUT_PATH=lib\RTC5\RTC5OUT.out"
set "DAT_PATH=lib\RTC5\RTC5DAT.dat"
set "RBF_PATH=lib\RTC5\RTC5RBF.rbf"
set "OUTPUT_DIR=LaserProgram"
set "QT_ENV=C:\Windows\System32\cmd.exe /A /Q /K E:\Repo\Qt\5.15.18\mingw81_32\bin\qtenv2.bat"


rem 清理output文件夹 创建一个新的
if exist "%OUTPUT_DIR%" (
    echo Removing old output folder...
    rmdir /s /q "%OUTPUT_DIR%"
)
mkdir "%OUTPUT_DIR%"

rem 查找Build文件夹下 Release/Debug 结尾的目录, 复制构建exe
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

rem 拷贝 DLL/
if exist "%DLL_PATH%" (
    copy "%DLL_PATH%" "%OUTPUT_DIR%\"

) else (
    echo Can not find RTC5DLLx64.dll,exit.
    exit /b 1
)

rem 拷贝 RBF/DAT/OUT
if exist "%DLL_PATH%" (
    copy "%RBF_PATH%" "%OUTPUT_DIR%\"
    copy "%DAT_PATH%" "%OUTPUT_DIR%\"
    copy "%OUT_PATH%" "%OUTPUT_DIR%\"
) else (
    echo Can not find RBF/DATOUT,exit.
    exit /b 1
)

rem 打开新终端 执行 qtenv2 和 windeployqt 打包
echo open Qt pack tool windeployqt and start packing software...
start "" cmd.exe /K "cd /d %cd%\%OUTPUT_DIR% && call E:\Repo\Qt\5.15.18\mingw81_64\bin\qtenv2.bat &&  cd E:\Repo\LaserCAD_QT\%OUTPUT_DIR% && windeployqt LaserCAD.exe"

rem 等待打包完成
echo Waiting for windeployqt to finish...
timeout /t 5 >nul

rem 拷贝 output 到 F盘
echo Copying output to F:\%OUTPUT_DIR% ...
xcopy "%OUTPUT_DIR%" "F:\%OUTPUT_DIR%" /E /I /Y
echo Finished copying to F:\%OUTPUT_DIR%

rem 删除项目中output 文件夹
echo Removing local output folder...
rmdir /s /q "%OUTPUT_DIR%"


echo finish packing.
pause
