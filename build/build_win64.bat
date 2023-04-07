pushd "%~dp0"

"%~dp0/../tools/premake5/premake5.exe" --file=%~dp0/premake5.lua vs2022
@echo off
popd
if NOT ["%errorlevel%"]==["0"] pause
pause
