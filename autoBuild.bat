@echo off
setlocal enabledelayedexpansion

rem 设置路径变量
set "BUILD_DIR=build"
set "TARGET_EXE=LaserCAD.exe"
set "OUTPUT_DIR=output"
set "DLL_PATH=lib\RTC5\RTC5DLLx64.dll"
set "QT_ENV=C:\Windows\System32\cmd.exe /A /Q /K E:\Repo\Qt\5.15.18\mingw81_32\bin\qtenv2.bat"

rem 清理旧输出
if exist "%OUTPUT_DIR%" (
    echo Removing old output folder...
    rmdir /s /q "%OUTPUT_DIR%"
)
mkdir "%OUTPUT_DIR%"

rem 查找 Release 结尾的目录
for /d %%D in (%BUILD_DIR%\*Release) do (
    if exist "%%D\%TARGET_EXE%" (
        echo Found: %%D\%TARGET_EXE%
        copy "%%D\%TARGET_EXE%" "%OUTPUT_DIR%\"
        goto :found_exe
    )
)

echo 未找到带 LaserCAD.exe 的 Release 文件夹，退出。
exit /b 1

:found_exe

rem 拷贝 DLL
if exist "%DLL_PATH%" (
    copy "%DLL_PATH%" "%OUTPUT_DIR%\"
) else (
    echo 找不到 RTC5DLLx64.dll，退出。
    exit /b 1
)

rem 打开终端，自动执行 qtenv2 和 windeployqt
echo 启动 Qt 环境终端并自动执行 windeployqt...
start "" cmd.exe /K "cd /d %cd%\%OUTPUT_DIR% && call E:\Repo\Qt\5.15.18\mingw81_64\bin\qtenv2.bat &&  cd E:\Repo\LaserCAD_QT\output && windeployqt LaserCAD.exe"

echo 构建打包完成。
pause
