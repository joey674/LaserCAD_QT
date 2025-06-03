@echo off
setlocal enabledelayedexpansion

rem 设置部署类型
set "PROJECT_TYPE=Debug"
set "SYSTEM_ARCHITECTURE=x86"
@REM set "PROJECT_TYPE = Release"

rem 设置路径变量
set "PROJECT_ABS_PATH=E:\Repo\LaserCAD_QT"
set "BUILD_REL_DIR=build"
set "OUTPUT_REL_DIR=LaserProgram"
set "TARGET_NAME=LaserCAD.exe"
set "DLL_REL_PATH=lib\RTC5\RTC5DLL.dll"
set "OUT_REL_PATH=static\RTC5\RTC5OUT.out"
set "DAT_REL_PATH=static\RTC5\RTC5DAT.dat"
set "RBF_REL_PATH=static\RTC5\RTC5RBF.rbf"
set "CORRECTIONFILE_REL_DIR=static\CorrectionFiles"

rem env是32bit的
@REM set "QT_ENV=E:\Repo\Qt\5.15.18\mingw81_32\bin\qtenv2.bat"
set "QT_ENV=C:\Qt\5.15.19\mingw81_32\bin\qtenv2.bat"

rem 清理output文件夹 创建一个新的
if exist "%OUTPUT_REL_DIR%" (
    echo Removing old output folder...
    rmdir /s /q "%OUTPUT_REL_DIR%"
)
mkdir "%OUTPUT_REL_DIR%"

rem 查找Build文件夹下 Release/Debug 结尾的目录, 复制构建exe
for /d %%D in (%BUILD_REL_DIR%\*%PROJECT_TYPE%) do (
    if exist "%%D\%TARGET_NAME%" (
        echo Found: %%D\%TARGET_NAME%
        copy "%%D\%TARGET_NAME%" "%OUTPUT_REL_DIR%\"
        goto :found_exe
    )
)
echo Can not find LaserCAD.exe in Build folder. please build the project in Qt first.
exit /b 1
:found_exe

rem 拷贝 DLL/
if exist "%DLL_REL_PATH%" (
    copy "%DLL_REL_PATH%" "%OUTPUT_REL_DIR%\"
) else (
    echo Can not find RTC5DLLx64.dll,exit.
    exit /b 1
)

rem 拷贝 RBF/DAT/OUT
if exist "%DLL_REL_PATH%" (
    copy "%RBF_REL_PATH%" "%OUTPUT_REL_DIR%\"
    copy "%DAT_REL_PATH%" "%OUTPUT_REL_DIR%\"
    copy "%OUT_REL_PATH%" "%OUTPUT_REL_DIR%\"
) else (
    echo Can not find RBF/DATOUT,exit.
    exit /b 1
)

rem 拷贝 CorrectionFiles
if exist "%CORRECTIONFILE_REL_DIR%" (
    xcopy /E /I /Y "%CORRECTIONFILE_REL_DIR%" "%OUTPUT_REL_DIR%\CorrectionFiles"
) else (
    echo CorrectionFiles folder not found.
    exit /b 1
)

rem 打开新终端 执行 qtenv2 和 windeployqt 打包
echo open Qt pack tool windeployqt and start packing software...
start "" cmd.exe /C "call %QT_ENV% && cd /d %PROJECT_ABS_PATH%\%OUTPUT_REL_DIR% && windeployqt %TARGET_NAME%"

rem 等待打包完成
echo Waiting for windeployqt to finish...
timeout /t 5 >nul

rem 删除 F盘 中旧的outout
echo Removing  output folder in F:...
rmdir /s /q "F:\%OUTPUT_REL_DIR%"

rem 拷贝 output 到 F盘
echo Copying output to F:\%OUTPUT_REL_DIR% ...
xcopy "%OUTPUT_REL_DIR%" "F:\%OUTPUT_REL_DIR%" /E /I /Y
echo Finished copying to F:\%OUTPUT_REL_DIR%

rem 删除项目中output 文件夹
echo Removing local output folder...
rmdir /s /q "%OUTPUT_REL_DIR%"


echo finish packing.
pause
