@echo off

net session >nul 2>&1 || (powershell start -verb runas '%~0' &exit /b)

COPY "%~dp0\Dependencies\DWin64\assimp-vc142-mt-x64d.dll" "C:\Windows\SysWOW64"
if /i exist "C:\Windows\SysWOW64\assimp-vc142-mt-x64d.dll" Echo assimp-vc142-mt-x64d.dll copied successfully to SysWOW64

COPY "%~dp0\Dependencies\DWin64\assimp-vc142-mt-x64d.dll" "C:\Windows\System32"
if /i exist "C:\Windows\System32\assimp-vc142-mt-x64d.dll" Echo assimp-vc142-mt-x64d.dll copied successfully to System32

pause