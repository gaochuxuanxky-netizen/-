@echo off
chcp 65001 >nul
echo 正在打包 release 目录...
C:\msys64\usr\bin\bash.exe -lc "export PATH=/ucrt64/bin:/usr/bin:$PATH && cd /c/Users/YOGA/Desktop/SmartPath-Qt && rm -rf release && mkdir -p release && cp build_msys/SmartPath.exe release/ && cp /ucrt64/bin/libgcc_s_seh-1.dll /ucrt64/bin/libstdc++-6.dll /ucrt64/bin/libwinpthread-1.dll release/ && windeployqt6 --no-translations release/SmartPath.exe"
if errorlevel 1 (
    echo 打包过程有警告，请检查 release 目录。
) else (
    echo 打包完成：release\SmartPath.exe
)
pause
