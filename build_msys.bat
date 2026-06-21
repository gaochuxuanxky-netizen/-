@echo off
chcp 65001 >nul
echo 正在编译 SmartPath（Qt 6 + MSYS2）...
C:\msys64\usr\bin\bash.exe -lc "export PATH=/ucrt64/bin:/usr/bin:$PATH && cd /c/Users/YOGA/Desktop/SmartPath-Qt && mkdir -p build_msys && cd build_msys && cmake .. -DCMAKE_PREFIX_PATH=/ucrt64 -G Ninja && ninja"
if errorlevel 1 (
    echo 编译失败，请确认已安装 MSYS2 及 Qt6 组件（pacman -S mingw-w64-ucrt-x86_64-qt6-base）。
    pause
    exit /b 1
)
echo 编译成功：build_msys\SmartPath.exe
pause
